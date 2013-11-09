#include "components.h"

// the output mode
BOOL out;

void dfs_component(NODE* nodes, BYTE x, BYTE y, BYTE z, BYTE c) {
  INT p = pos(x,y,z);
  if (nodes[p].component > 0)
    return;
  if (nodes[p].component < 0) {
    fprintf(stderr, "dfs_component: %c%c%c %d %d", x + 'a', y + 'a', z + 'a', nodes[p].component, c);
    return;
  }
  if (out) printf("%c%c%c,", x + 'a', y + 'a', z + 'a');
  NODE n;
  nodes[p].component = c;
  BYTE i;
  n = nodes[p]; for (i = n.next[0]; i != -1; n = nodes[pos(i,y,z)],i = n.next[0]) dfs_component(nodes, i,y,z,c);
  n = nodes[p]; for (i = n.prev[0]; i != -1; n = nodes[pos(i,y,z)],i = n.prev[0]) dfs_component(nodes, i,y,z,c);
  n = nodes[p]; for (i = n.next[1]; i != -1; n = nodes[pos(x,i,z)],i = n.next[1]) dfs_component(nodes, x,i,z,c);
  n = nodes[p]; for (i = n.prev[1]; i != -1; n = nodes[pos(x,i,z)],i = n.prev[1]) dfs_component(nodes, x,i,z,c);
  n = nodes[p]; for (i = n.next[2]; i != -1; n = nodes[pos(x,y,i)],i = n.next[2]) dfs_component(nodes, x,y,i,c);
  n = nodes[p]; for (i = n.prev[2]; i != -1; n = nodes[pos(x,y,i)],i = n.prev[2]) dfs_component(nodes, x,y,i,c);
}

int findComponents(NODE* nodes, BOOL output) {
  BYTE x,y,z;
  INT c,p;
  out = output;
  c = 1;
  for (z = 0; z < LEN; z++) {
    for (y = 0; y < LEN; y++) {
      for (x = 0; x < LEN; x++) {
        p = pos(x,y,z);
        if (nodes[p].component != 0)
          continue;
        if (out) printf("Component #%d:\n", c, x+'a', y+'a', z+'a');
        dfs_component(nodes, x,y,z,c);
        if (out) printf("\n\n");
        c++;
      }
    }
  }
  return c - 1;
}
