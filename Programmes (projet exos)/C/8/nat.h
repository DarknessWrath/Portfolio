//  définitions du nom de type nat et de macroconstantes liées. Ces définitions
//    sont sensibles à la définition de la macroconstante NATWIDTH. Les valeurs
//    possibles pour NATWIDTH sont 8, 16, 32 ou 64, la valeur par défaut est 32

#ifndef NAT__H
#define NAT__H

#include <inttypes.h>

#ifndef NATWIDTH
#define NATWIDTH 32
#endif

#if NATWIDTH == 8

typedef uint8_t nat;

#define NAT_MAX  UINT8_MAX

#define NAT_PRI PRIu8
#define NAT_SCN SCNu8

#elif NATWIDTH == 16

typedef uint16_t nat;

#define NAT_MAX  UINT16_MAX

#define NAT_PRI PRIu16
#define NAT_SCN SCNu16

#elif NATWIDTH == 32

typedef uint32_t nat;

#define NAT_MAX  UINT32_MAX

#define NAT_PRI PRIu32
#define NAT_SCN SCNu32

#elif NATWIDTH == 64

typedef uint64_t nat;

#define NAT_MAX  UINT64_MAX

#define NAT_PRI PRIu64
#define NAT_SCN SCNu64

#else
#error Illegal value of NATWIDTH
#endif

#endif
