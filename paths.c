#include "paths.h"

#define dfs_path_step(a,b,c) { \
          if (d + 1 < nodes[pos(a,b,c)].dist) { \
            nodes[pos(a,b,c)].prevX = x; \
            nodes[pos(a,b,c)].prevY = y; \
            nodes[pos(a,b,c)].prevZ = z; \
            dfs_path(nodes, a, b, c, tx, ty, tz, d + 1); \
          } \
        }

void dfs_path(NODE* nodes, BYTE x, BYTE y, BYTE z, BYTE tx, BYTE ty, BYTE tz, INT d) {
  INT p = pos(x,y,z);
  if (nodes[p].component < 0) {
    fprintf(stderr, "dfs_path: %c%c%c\n", CHARS(x,y,z));
    return;
  }
  nodes[p].dist = d; 
  if (x == tx && y == ty && z == tz)
    return;
  NODE n;
  BYTE i;
  n = nodes[p]; for (i = n.next[0]; i != -1; n = nodes[pos(i,y,z)],i = n.next[0]) dfs_path_step(i,y,z)
  n = nodes[p]; for (i = n.prev[0]; i != -1; n = nodes[pos(i,y,z)],i = n.prev[0]) dfs_path_step(i,y,z)
  n = nodes[p]; for (i = n.next[1]; i != -1; n = nodes[pos(x,i,z)],i = n.next[1]) dfs_path_step(x,i,z)
  n = nodes[p]; for (i = n.prev[1]; i != -1; n = nodes[pos(x,i,z)],i = n.prev[1]) dfs_path_step(x,i,z)
  n = nodes[p]; for (i = n.next[2]; i != -1; n = nodes[pos(x,y,i)],i = n.next[2]) dfs_path_step(x,y,i)
  n = nodes[p]; for (i = n.prev[2]; i != -1; n = nodes[pos(x,y,i)],i = n.prev[2]) dfs_path_step(x,y,i)
}

void initDFS(NODE* nodes) {
  INT i;
  for (i = 0; i < LEN3; i++) {
    nodes[i].dist = MAX_INT;
    nodes[i].prevX = -1;
    nodes[i].prevY = -1;
    nodes[i].prevZ = -1;
  }
}

INT shortestPath(NODE* nodes, BYTE x1, BYTE y1, BYTE z1, BYTE x2, BYTE y2, BYTE z2, BOOL output) {
  initDFS(nodes);
  if (nodes[pos(x1,y1,z1)].component != nodes[pos(x2,y2,z2)].component || nodes[pos(x1,y1,z1)].component < 0)
    return -1;
  dfs_path(nodes, x2, y2, z2, x1, y1, z1, 0);
  if (output) {
    printf("Shortest path from %c%c%c to %c%c%c\n", CHARS(x1,y1,z1), CHARS(x2,y2,z2));
    BYTE xi = x1, yi = y1, zi = z1;
    do {
      NODE ni = nodes[pos(xi,yi,zi)];
      printf("%c%c%c-", CHARS(xi,yi,zi), nodes[pos(xi,yi,zi)].dist);
      xi = ni.prevX;
      yi = ni.prevY;
      zi = ni.prevZ;
    } while (xi != x2 || yi != y2 || zi != z2);
    printf("%c%c%c\n",CHARS(x2,y2,z2));
  }
  return nodes[pos(x1, y1, z1)].dist;
}
