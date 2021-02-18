//  petit jeu sur les polynômes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "double_base.h"
#include "double_poly.h"

//--- Autour de la fonction principale -----------------------------------------

static void usage(const char *progname);
static void print_err_unexpected_gobble_line(const char *s, int unexpected);

typedef struct {
  int label;
  poly p;
} memory;

#define MEMORY_NBR      8
#define CMD_NPARAM_MAX  2

typedef struct {
  memory ammr[MEMORY_NBR];
  int last;
  size_t immr[CMD_NPARAM_MAX];
} control;

static void memory_init(control *ctrlptr);
static int memory_get(control *ctrlptr, int idx);

#define NORMAL_QUIT    ((char *) "May the Pforce be with you!")
#define ABNORMAL_QUIT  ((char *) "Inelegant quit")

static void game_help(control *ctrlptr);
static void game_quit(void);
static void game_null(control *ctrlptr);
static void game_copy(control *ctrlptr);
static void game_scan(control *ctrlptr);
static void game_print(control *ctrlptr);
static void game_opposite(control *ctrlptr);
static void game_derivative(control *ctrlptr);
static void game_advance(control *ctrlptr);
static void game_multiply(control *ctrlptr);
static void game_evaluate(control *ctrlptr);

typedef struct {
  const char label;
  const char *comment;
  int nparam;
  union {
    void (*v)(void);
    void (*m)(control *ctrlptr);
  } action;
} scmd;

scmd acmd[] = {
  {
    .label = 'h',
    .comment = "print this help",
    .nparam = 0,
    .action.m = game_help,
  },
  {
    .label = 'q',
    .comment = "quit this game",
    .nparam = -1,
    .action.v = game_quit,
  },
  {
    .label = 'a',
    .comment = "advance %s by %s",
    .nparam = 2,
    .action.m = game_advance,
  },
  {
    .label = 'c',
    .comment = "initialize %s by copying %s",
    .nparam = 2,
    .action.m = game_copy,
  },
  {
    .label = 'd',
    .comment = "replace %s by its derivative",
    .nparam = 1,
    .action.m = game_derivative,
  },
  {
    .label = 'e',
    .comment = "evaluate %s for a list of values ended by a new-line",
    .nparam = 1,
    .action.m = game_evaluate,
  },
  {
    .label = 'm',
    .comment = "multiply %s by %s",
    .nparam = 2,
    .action.m = game_multiply,
  },
  {
    .label = 'n',
    .comment = "initialize %s to null",
    .nparam = 1,
    .action.m = game_null,
  },
  {
    .label = 'o',
    .comment = "replace %s by its opposite",
    .nparam = 1,
    .action.m = game_opposite,
  },
  {
    .label = 'p',
    .comment = "print %s",
    .nparam = 1,
    .action.m = game_print,
  },
  {
    .label = 's',
    .comment = "initialize %s with a list of values ended by a new-line",
    .nparam = 1,
    .action.m = game_scan,
  },
};

#define PROMPT_WAIT   "? "
#define PROMPT_RESULT "= "

#define ARG__OPT_LONG "--"
#define ARG_HELP      "help"

int main(int argc, char *argv[]) {
  //
  //--- initialisation
  //
  control ctrl;
  memory_init(&ctrl);
  //
  //--- help
  //
  //  IB : 1 <= k && k <= argc
  //    && aucune des chaines argv[1] à argv[k - 1] n'est préfixe de
  //        ARG__OPT_LONG . ARG_HELP ou n'admet ARG__OPT_LONG . ARG_HELP[0]
  //        comme préfixe
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *a = argv[k];
    if (strlen(a) > strlen(ARG__OPT_LONG)
        && strlen(a) <= strlen(ARG__OPT_LONG ARG_HELP)
        && strncmp(a, ARG__OPT_LONG ARG_HELP, strlen(a)) == 0) {
      usage(argv[0]);
    }
  }
  //
  //--- jeu
  //
  game_help(&ctrl);
  int c = '\n';
  //  IB : c == dernière valeur renvoyée par getchar()
  //    && toutes les commandes passées ont été traitées sauf la dernière si
  //        c != EOF
  //  QC : nombre d'appels à getchar()
  do {
    if (isspace(c)) {
      if (c == '\n') {
        printf(PROMPT_WAIT);
      }
    } else {
      const scmd *p = acmd;
      //  IB : acmd <= p && p <= acmd + sizeof(acmd) / sizeof(*acmd)
      //    && et(acmd[q - acmd].label != c ; acmd <= q && q < p)
      //  QC : p - acmd
      while (p < acmd + sizeof(acmd) / sizeof(*acmd) && p -> label != c) {
        ++p;
      }
      if (p == acmd + sizeof(acmd) / sizeof(*acmd)) {
        print_err_unexpected_gobble_line("Unknown command", c);
      } else {
        if (p -> nparam == -1) {
          p -> action.v();
          if (p -> action.v == game_quit) {
            break;
          }
        } else {
          int i = 0;
          //  IB : 0 <= i && i <= p -> nparam
          //    && et(memory_get(&ctrl, j) == 0 ; 0 <= j && j < i)
          //  QC : i
          while (i < p -> nparam && memory_get(&ctrl, i) == 0) {
            ++i;
          }
          if (i < p -> nparam) {
            print_err_unexpected_gobble_line("Unknown memory", ctrl.last);
          } else {
            p -> action.m(&ctrl);
          }
        }
      }
    }
    c = getchar();
  } while (c != EOF);
  char *r = (c == EOF ? ABNORMAL_QUIT : NORMAL_QUIT);
  //
  //--- fin du jeu
  //
  printf("\n%s\n", r);
  return EXIT_SUCCESS;
}

//--- Développements -----------------------------------------------------------

void usage(const char *progname) {
  printf("Usage: %s\n", progname);
  printf("Small game on polynomes.\n");
  printf("\n");
  printf("  " ARG__OPT_LONG ARG_HELP "  display this help and exit\n");
  printf("\n");
  exit(EXIT_SUCCESS);
}

void print_err_unexpected_gobble_line(const char *s, int unexpected) {
  fprintf(stderr, "*** %s: '%c'\n", s, unexpected);
  int c = getchar();
  //  IB : c == dernière valeur renvoyée par getchar()
  //    && aucun des caractères lus, sans compter le dernier si c != EOF, n'est
  //          égal à '\n'
  //  QC : nombre d'appels à getchar()
  while (c != EOF && c != '\n') {
    c = getchar();
  }
  ungetc(c, stdin);
}

void memory_init(control *ctrlptr) {
  int c = 0;
  //  IB : 0 <= k && k <= MEMORY_NBR
  //    && les valeurs ctrlptr -> ammr[j].label pour j == 0 ... k - 1 sont des
  //        lettres capitales deux à deux différentes
  //    && la valeur de ctrlptr -> ammr[j].p est le polynôme nul pour
  //        j == 0 ... k - 1
  //  QC : k
  for (size_t k = 0; k < MEMORY_NBR; ++k) {
    while (c <= UCHAR_MAX && ! isupper(c)) {
      ++c;
    }
    if (c > UCHAR_MAX) {
      fprintf(stderr, "*** Internal error: "
          "Incorrect number of memories '%d'.\n", MEMORY_NBR);
      abort();
    }
    ctrlptr -> ammr[k].label = c;
    poly_null(& ctrlptr -> ammr[k].p);
    ++c;
  }
}

int memory_get(control *ctrlptr, int idx) {
  int c;
  do {
    c = getchar();
  } while (isspace(c));
  if (c == EOF) {
    ctrlptr -> last = '#';
    return -1;
  }
  ctrlptr -> last = c;
  size_t k = 0;
  //  IB : 0 <= k && k <= MEMORY_NBR
  //    && et(ctrlptr -> ammr[j].label != c ; j == 0 ... k - 1)
  //  QC : k
  while (k < MEMORY_NBR && ctrlptr -> ammr[k].label != c) {
    ++k;
  }
  if (k == MEMORY_NBR) {
    return -1;
  }
  ctrlptr -> immr[idx] = k;
  return 0;
}

#define HELP_MEMORY_FIRST   "R"
#define HELP_MEMORY_SECOND  "S"

void game_help(control *ctrlptr) {
  printf("Polynome memories are letters from %c to %c.\n",
      ctrlptr -> ammr[0].label, ctrlptr -> ammr[MEMORY_NBR - 1].label);
  printf("In the following list of commands, %s and %s mean any of "
      "but different memories.\n",
      HELP_MEMORY_FIRST, HELP_MEMORY_SECOND);
  printf("\nCommands:\n");
  //  IB : acmd <= p && p <= acmd + sizeof(acmd) / sizeof(*acmd)
  //    && (toutes les commandes pointée par q tel que acmd <= q && q < p ont
  //        été affichées)
  //  QC : p - acmd
  for (scmd *p = acmd; p < acmd + sizeof(acmd) / sizeof(*acmd); ++p) {
    printf("%3c ", p -> label);
    if (p -> nparam >= 1) {
      printf("%s ", HELP_MEMORY_FIRST);
    }
    if (p -> nparam >= 2) {
      printf("%s ", HELP_MEMORY_SECOND);
    }
    printf("%*s  ", 4 - 2 * (p -> nparam < 0 ? 0 : p -> nparam), "");
    printf(p -> comment, HELP_MEMORY_FIRST, HELP_MEMORY_SECOND);
    printf("\n");
  }
  printf("\n");
}

void game_quit(void) {
}

void game_null(control *ctrlptr) {
  poly_null(& ctrlptr -> ammr[ctrlptr -> immr[0]].p);
}

void game_copy(control *ctrlptr) {
  poly_copy(& ctrlptr -> ammr[ctrlptr -> immr[0]].p,
      & ctrlptr -> ammr[ctrlptr -> immr[1]].p);
}

void game_scan(control *ctrlptr) {
  if (poly_scan(& ctrlptr -> ammr[ctrlptr -> immr[0]].p) != 0) {
    fprintf(stderr, "*** Read error\n");
  }
}

void game_print(control *ctrlptr) {
  printf("[%c] " PROMPT_RESULT, ctrlptr -> ammr[ctrlptr -> immr[0]].label);
  poly_print(& ctrlptr -> ammr[ctrlptr -> immr[0]].p);
  printf("\n");
}

void game_opposite(control *ctrlptr) {
  poly_opposite(& ctrlptr -> ammr[ctrlptr -> immr[0]].p);
}

void game_derivative(control *ctrlptr) {
  poly_derivative(& ctrlptr -> ammr[ctrlptr -> immr[0]].p);
}

void game_advance(control *ctrlptr) {
  poly_add(& ctrlptr -> ammr[ctrlptr -> immr[0]].p,
      & ctrlptr -> ammr[ctrlptr -> immr[1]].p);
}

void game_multiply(control *ctrlptr) {
  if (poly_multiply(& ctrlptr -> ammr[ctrlptr -> immr[0]].p,
      & ctrlptr -> ammr[ctrlptr -> immr[1]].p) != 0) {
    fprintf(stderr, "*** Overflow\n");
  }
}

void game_evaluate(control *ctrlptr) {
  double x;
  int rs = double_scan(&x);
  //  IB : rs == (dernière valeur renvoyée par double_scan(&x))
  //    && x == (dernière valeur lue si rs == 1)
  //    && (les résultats des évaluations du polynôme *ptr en chacune des
  //        valeurs lues sauf la dernière si rs == 1 ont été affichés)
  //  QC : nombre d'appels à scanf
  while (rs == 1) {
    printf("(");
    double_print(x);
    printf(") " PROMPT_RESULT);
    double_print(poly_evaluate(& ctrlptr -> ammr[ctrlptr -> immr[0]].p, x));
    printf("\n");
    rs = double_scan(&x);
  }
  if (rs != 0) {
    fprintf(stderr, "*** Read error\n");
  }
}
