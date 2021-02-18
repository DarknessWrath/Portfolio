//  petit jeu sur la suite de Collatz utilisant un fichier binaire homogène de
//    nom désigné par la macroconstante FILENAME et sur un type entier naturel
//    de nom désigné par nat
//  Le nom nat et les macroconstantes NAT_MAX, NAT_PRI et NAT_SCN sont définis
//    dans l'en-tête "nat.h"

#define FILENAME "tmp.bin"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "nat.h"
#include "fnat.h"

//--- Autour de la fonction principale -----------------------------------------

static void usage(const char *progname);
static nat nat_sget(const char *progname, const char *label, const char *s,
    nat min, nat max);
static long int lint_sget(const char *progname, const char *label,
    const char *s, long int min, long int max);
static void exit_failure(const char *progname, const char *format,
    const char *arg);
static void print_err_gobble_line(const char *s);

typedef enum {
  CMD_HELP,
  CMD_QUIT,
  CMD_PRINT_ALL,
  CMD_PRINT_TERM,
  CMD_PRINT_INDEX,
} cmd;

typedef enum {
  ACTION_VOID,
  ACTION_CTRL,
} action;

typedef char *result;

#define RESULT_CONTINUE       NULL
#define RESULT_NORMAL_QUIT    ((char *) "\nMay the Cforce be with you!\n")
#define RESULT_ABNORMAL_QUIT  ((char *) "\nInelegant quit\n")

typedef struct {
  nat seed;
  long int length;
  FILE *stream;
} control;

static result game_help(control *ctrlptr);
static result game_quit(void);
static result game_print_all(control *ctrlptr);
static result game_print_term(control *ctrlptr);
static result game_print_index(control *ctrlptr);

typedef struct {
  int label;
  char *comment;
  char *param;
  action act;
  union {
    result (*action_void)(void);
    result (*action_ctrl)(control *ctrlptr);
  };
} scmd;

const scmd acmd[] = {
  [CMD_HELP] = {
    .label = 'h',
    .comment = "print this help",
    .param = NULL,
    .act = ACTION_CTRL,
    .action_ctrl = game_help,
  },
  [CMD_QUIT] = {
    .label = 'q',
    .comment = "quit this game",
    .param = NULL,
    .act = ACTION_VOID,
    .action_void = game_quit,
  },
  [CMD_PRINT_ALL] = {
    .label = 'p',
    .comment = "print the sequence <C(seed, n)>",
    .param = NULL,
    .act = ACTION_CTRL,
    .action_ctrl = game_print_all,
  },
  [CMD_PRINT_TERM] = {
    .label = 't',
    .comment = "print the term C(seed, %s)",
    .param = "INDEX",
    .act = ACTION_CTRL,
    .action_ctrl = game_print_term,
  },
  [CMD_PRINT_INDEX] = {
    .label = 'i',
    .comment = "print the smallest index n such that C(seed, n) = %s",
    .param = "VALUE",
    .act = ACTION_CTRL,
    .action_ctrl = game_print_index,
  },
};

#define PROMPT_WAIT   "? "
#define PROMPT_RESULT "= "

#define ARG__OPT_LONG "--"
#define ARG_HELP      "help"

#define SEED_NAME    "SEED"
#define LENGTH_NAME  "LENGTH"

enum {
  PROGN_IDX,
  SEED_IDX,
  LENGTH_IDX,
  EXPECTED_ARGC
};

#define SEED_MIN    (nat) 1
#define SEED_MAX    NAT_MAX
#define LENGTH_MIN  0L
#define LENGTH_MAX  1000000L

int main(int argc, char *argv[]) {
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
  //--- paramètres
  //
  const char *progname = argv[0];
  control ctrl;
  if (argc != EXPECTED_ARGC) {
    exit_failure(progname, "Bad number of parameters", NULL);
  }
  ctrl.seed = nat_sget(progname, SEED_NAME, argv[SEED_IDX], SEED_MIN, SEED_MAX);
  ctrl.length = lint_sget(progname, LENGTH_NAME, argv[LENGTH_IDX], LENGTH_MIN,
      LENGTH_MAX);
  ctrl.stream = fnat_open_collatz(FILENAME, ctrl.seed, ctrl.length);
  if (ctrl.stream == NULL) {
    exit_failure(argv[0], "Creation of file '%s' aborted", FILENAME);
  }
  //
  //--- jeu
  //
  game_help(&ctrl);
  result r = RESULT_CONTINUE;
  int c = '\n';
  //  IB : c == dernière valeur renvoyée par getc(stdin)
  //    && toutes les commandes passées ont été traitées sauf la dernière si
  //        c != EOF
  //  QC : nombre d'appels à getc(stdin)
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
        print_err_gobble_line("unknown command");
      } else {
        switch (p -> act) {
          case ACTION_VOID:
            r = p -> action_void();
            break;
          case ACTION_CTRL:
            r = p -> action_ctrl(&ctrl);
            break;
        }
        if (r == RESULT_NORMAL_QUIT) {
          break;
        }
      }
    }
    c = getc(stdin);
  } while (c != EOF);
  if (r != RESULT_NORMAL_QUIT) {
    r = RESULT_ABNORMAL_QUIT;
  }
  //
  //--- fin du jeu
  //
  if (fclose(ctrl.stream) != 0) {
    exit_failure(NULL, "Error encountered at file closure", NULL);
  }
  if (remove(FILENAME) != 0) {
    exit_failure(NULL, "Error encountered at file removal", NULL);
  }
  puts(r);
  return EXIT_SUCCESS;
}

//--- Développements -----------------------------------------------------------

#define ERR_MSG_READ  "An error occured while reading the file"

void usage(const char *progname) {
  printf("Usage: %s " SEED_NAME " " LENGTH_NAME "\n", progname);
  printf("Small game on"
      " the prefix of length " LENGTH_NAME
      " of the Collatz sequence"
      " of seed " SEED_NAME ".\n");
  printf("\n");
  printf(SEED_NAME " range: %" NAT_PRI " - %" NAT_PRI "\n", SEED_MIN, SEED_MAX);
  printf(LENGTH_NAME " range: %ld - %ld\n", LENGTH_MIN, LENGTH_MAX);
  printf("\n");
  printf("  " ARG__OPT_LONG ARG_HELP "  display this help and exit\n");
  printf("\n");
  exit(EXIT_SUCCESS);
}

nat nat_sget(const char *progname, const char *label, const char *s, nat min,
    nat max) {
  uintmax_t n;
  char *p;
  errno = 0;
  n = strtoumax(s, &p, 10);
  if (errno != 0 || *p != '\0') {
    exit_failure(progname, "%s parameter can not be read as a number", label);
  }
  if (n < min || n > max) {
    exit_failure(progname, "%s parameter is out of range", label);
  }
  return (nat) n;
}

long int lint_sget(const char *progname, const char *label, const char *s,
    long int min, long int max) {
  long int n;
  char *p;
  errno = 0;
  n = strtol(s, &p, 10);
  if (errno != 0 || *p != '\0') {
    exit_failure(progname, "%s parameter can not be read as a number", label);
  }
  if (n < min || n > max) {
    exit_failure(progname, "%s parameter is out of range", label);
  }
  return n;
}

void exit_failure(const char *progname, const char *format,
    const char *arg) {
  fprintf(stderr, format, arg);
  fprintf(stderr, ".\n");
  if (progname != NULL) {
    fprintf(stderr, "Try '%s " ARG__OPT_LONG ARG_HELP "'.\n", progname);
  }
  exit(EXIT_FAILURE);
}

void print_err_gobble_line(const char *s) {
  fprintf(stderr, "*** %s\n", s);
  int c = getc(stdin);
  while (c != EOF && c != '\n') {
    c = getc(stdin);
  }
  if (c != EOF) {
    ungetc('\n', stdin);
  }
}

result game_help(control *ctrlptr) {
  printf("Size of natural type: %zu bytes.\n", sizeof(nat));
  printf("Maximum value of natural type: %" NAT_PRI ".\n", NAT_MAX);
  printf("Seed: %" NAT_PRI ".\n", ctrlptr -> seed);
  printf("Length: %ld.\n", ctrlptr -> length);
  printf("Commands:\n");
  //  IB : acmd <= p && p <= acmd + sizeof(acmd) / sizeof(*acmd)
  //    && et(l'aide pour acmd[q - acmd] a été affichée ; acmd <= q && q < p)
  //  QC : p - acmd
  for (const scmd *p = acmd; p < acmd + sizeof(acmd) / sizeof(*acmd); ++p) {
    printf("%3c ", p -> label);
    printf("%-6s  ", p -> param == NULL ? "" : p -> param);
    printf(p -> comment, p -> param);
    printf("\n");
  }
  printf("\n");
  return RESULT_CONTINUE;
}

result game_quit(void) {
  return RESULT_NORMAL_QUIT;
}

result game_print_all(control *ctrlptr) {
  if (fnat_print(ctrlptr -> stream) != 0) {
    print_err_gobble_line(ERR_MSG_READ);
  }
  return RESULT_CONTINUE;
}

result game_print_term(control *ctrlptr) {
  long int n;
  nat x;
  errno = 0;
  if (scanf("%ld", &n) != 1 || errno != 0 || n < 0) {
    print_err_gobble_line("Invalid index value");
  } else if (fnat_index_to_value(ctrlptr -> stream, n, &x) != 0) {
    print_err_gobble_line(ERR_MSG_READ " or index out of range");
  } else {
    printf(PROMPT_RESULT "%" NAT_PRI "\n", x);
  }
  return RESULT_CONTINUE;
}

result game_print_index(control *ctrlptr) {
  nat x;
  long int n;
  if (scanf("%" NAT_SCN , &x) != 1) {
    print_err_gobble_line("Invalid nat value");
  } else if (fnat_value_to_index(ctrlptr -> stream, x, &n) != 0) {
    print_err_gobble_line(ERR_MSG_READ " or term not found");
  } else {
    printf(PROMPT_RESULT "%ld\n", n);
  }
  return RESULT_CONTINUE;
}
