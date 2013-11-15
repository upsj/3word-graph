#include "degrees.h"

void o(BYTE x, BYTE y, BYTE z) {
  printf("%c%c%c ",CHARS(x,y,z));
}

BYTE degree (NODE* nodes, BYTE x, BYTE y, BYTE z, BOOL output) {
  BYTE d = 0;
  NODE n;
  BYTE i;
  INT p = pos(x,y,z);
  n = nodes[p]; for (i = n.next[0]; i != -1; n = nodes[pos(i,y,z)],i = n.next[0]) d++;
  n = nodes[p]; for (i = n.prev[0]; i != -1; n = nodes[pos(i,y,z)],i = n.prev[0]) d++;
  n = nodes[p]; for (i = n.next[1]; i != -1; n = nodes[pos(x,i,z)],i = n.next[1]) d++;
  n = nodes[p]; for (i = n.prev[1]; i != -1; n = nodes[pos(x,i,z)],i = n.prev[1]) d++;
  n = nodes[p]; for (i = n.next[2]; i != -1; n = nodes[pos(x,y,i)],i = n.next[2]) d++;
  n = nodes[p]; for (i = n.prev[2]; i != -1; n = nodes[pos(x,y,i)],i = n.prev[2]) d++;
  if (output) {
    o(x,y,z);
    printf("(%2d): ", d);
    n = nodes[p]; for (i = n.next[0]; i != -1; n = nodes[pos(i,y,z)],i = n.next[0]) o(i,y,z);
    n = nodes[p]; for (i = n.prev[0]; i != -1; n = nodes[pos(i,y,z)],i = n.prev[0]) o(i,y,z);
    n = nodes[p]; for (i = n.next[1]; i != -1; n = nodes[pos(x,i,z)],i = n.next[1]) o(x,i,z);
    n = nodes[p]; for (i = n.prev[1]; i != -1; n = nodes[pos(x,i,z)],i = n.prev[1]) o(x,i,z);
    n = nodes[p]; for (i = n.next[2]; i != -1; n = nodes[pos(x,y,i)],i = n.next[2]) o(x,y,i);
    n = nodes[p]; for (i = n.prev[2]; i != -1; n = nodes[pos(x,y,i)],i = n.prev[2]) o(x,y,i);
    printf("\n");
  }

  nodes[p].degree = d;
  return d;
}

void calcDegrees(NODE* nodes, BOOL stats, BOOL fullOutput) {
  BYTE x, y, z, d;
  BYTE maxD, maxX, maxY, maxZ;
  INT p;
  INT sumD = 0;
  maxD = -1;

  for (z = 0; z < LEN; z++) {
    for (y = 0; y < LEN; y++) {
      for (x = 0; x < LEN; x++) {
        p = pos(x, y, z);
        if (nodes[p].component < 0)
          continue;
        d = degree(nodes, x, y, z, fullOutput);
        sumD += d;
        if (d > maxD) {
          maxD = d;
          maxX = x;
          maxY = y;
          maxZ = z;
        }
      }
    }
  }

  if (stats) {
    printf("Sum of degrees: %d\n", sumD);
    printf("Maximal degree: \n");
    if (maxD >= 0) {
      degree(nodes, maxX, maxY, maxZ, TRUE);
    }
  }
}
