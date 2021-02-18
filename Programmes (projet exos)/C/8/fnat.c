#include "fnat.h"

#define FUN_SUCCESS 0
#define FUN_FAILURE -1

int fnat_print(FILE *stream) {
  long int k=0;
  nat x;
 rewind(stream);
  while(fread(&x, sizeof(nat), 1, stream) == 1) {
  printf("%ld\t %"NAT_PRI"\n", k, x);
  ++k;
  }
  if (! feof(stream)) {
    return FUN_FAILURE;
  }
  return FUN_SUCCESS;
}

int fnat_index_to_value(FILE *stream, long int index, nat *valueptr) {


  return FUN_FAILURE;
}

int fnat_value_to_index(FILE *stream, nat value, long int *indexptr) {
  return FUN_FAILURE;
}

FILE *fnat_open_collatz(const char *filename, nat seed,
    long int length) {

  FILE *f= fopen(filename, "w+b");
  if (f==NULL) {
    return NULL;
    }
  long int k=0;
  nat x= seed;
  //IB: 0<=k && k<=length && x est le terme de rang k de la suite de Collatz
  // && les k premiers termes de la suite ont été écrits dans f
  //QC: k
  while (k<length && fwrite(&x, sizeof(nat), 1, f) ==1) {

    if (x % 2 == 0) {
     x= x / 2;
    }
    else {
     x = 3 * x + 1;
    }
    ++k;
  }
  if (k < length) {
    fclose(f);
    remove(filename);
    return NULL;
  }
  return f;
}
