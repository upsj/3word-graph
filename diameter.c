#include "diameter.h"

void diameter(FILE* f1, INT size, NODE* nodes) {
  char *buf = malloc(5); // Reading buffer
  size_t buf_size = 5;
  ssize_t read; // Size of last line
  BYTE *words = malloc(3 * size * sizeof(BYTE));
  BYTE a,b,c,d,e,f; // Character indices
  BYTE ma=-1,mb=-1,mc=-1,md=-1,me=-1,mf=-1;
  INT max = 0;
  INT cur;
  INT i = 0, j = 0;

  while ((read = getline(&buf, &buf_size, f1)) != -1) {
    if (read < 3)
      continue;
    a = buf[0] - 'a';
    b = buf[1] - 'a';
    c = buf[2] - 'a';
    if (a > 25 || a < 0 || b > 25 || b < 0 || c > 25 || c < 0)
      continue;
    words[i++] = a;
    words[i++] = b;
    words[i++] = c;
  }
  
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size; j++) {
      a = words[3 * i + 0];
      b = words[3 * i + 1];
      c = words[3 * i + 2];
      d = words[3 * j + 0];
      e = words[3 * j + 1];
      f = words[3 * j + 2];
      cur = shortestPath(nodes, a, b, c, d, e, f, FALSE);
      if (cur > max) {
        max = cur;
        ma = a; mb = b; mc = c; md = d; me = e; mf = f;
      }
    }
  }
  shortestPath(nodes, ma, mb, mc, md, me, mf, TRUE);
}
