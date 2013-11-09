#ifndef _NODES_H
#define _NODES_H
#include "main.h"

// Array index for given coordinates
INT pos(BYTE x, BYTE y, BYTE z);

void init(NODE* nodes);

INT readWords(NODE* nodes, FILE* f_input);

void initNav(NODE* nodes, BYTE dim);

#endif
