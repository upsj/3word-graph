#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>

#define INT int32_t
#define MAX_INT 0x7fffffff
#define BYTE char
#define BOOL char
#define TRUE 1
#define FALSE 0
#define LEN 26
#define LEN3 LEN * LEN * LEN
#define CHARS(x,y,z) x+'a',y+'a',z+'a'

// A single word placed in a 3-dimensional cube (coordinates are letters)
typedef struct NODE { 
  // Component/group indicator for the word
  INT component;

  // Degree of the node/vertex
  INT degree;

  // distance to the start vertex for DFS
  INT dist;

  // prev word for DFS
  BYTE prevX;
  BYTE prevY;
  BYTE prevZ;

  // index in each dimension of the next/prev word (-1 if not existant)
  BYTE next[3];
  BYTE prev[3];
} NODE;

#endif
