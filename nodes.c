#include "nodes.h"

// Array index for given coordinates
INT pos(BYTE x, BYTE y, BYTE z) {
  return x + LEN * y + LEN * LEN * z;
}

// Array index for given coordinates with permutated x,y,z
INT pos2(BYTE x, BYTE y, BYTE z, BYTE dim) {
  if (dim == 0) {
    return pos(x,y,z);
  } else if (dim == 1) {
    return pos(y,x,z);
  } else if (dim == 2) {
    return pos(y,z,x);
  }
  return -1;
}

// Initialize the nodes with empty values
void init(NODE* nodes) {
  INT i;
  for (i = 0; i < LEN3; i++) {
    nodes[i].component = -1;
    nodes[i].degree = 0;
  }
}

INT readWords(NODE* nodes, FILE* f_input) {
  char* buf = malloc(5); // Reading buffer
  size_t buf_size = 5;
  INT line = 0; // Line counter
  ssize_t read; // Size of last line
  BYTE a,b,c; // Character indices
  INT wordCount = 0;

  // Read lines
  while ((read = getline(&buf, &buf_size, f_input)) != -1) {
    line++;
    // 3 letter words should be in each line
    if (read < 3) {
      fprintf(stderr, "Word too short in line %d: %s\n", line, buf);
      continue;
    }

    a = buf[0] - 'a';
    b = buf[1] - 'a';
    c = buf[2] - 'a';
    if (a > 25 || a < 0 || b > 25 || b < 0 || c > 25 || c < 0) {
      fprintf(stderr, "Not a lower case character in line %d: %s\n", line, buf);
      continue;
    }

    // Mark node as existing
    INT p = pos(a,b,c);
    nodes[p].component = 0;
    nodes[p].prev[0] = -1; nodes[p].prev[1] = -1; nodes[p].prev[2] = -1;
    nodes[p].next[0] = -1; nodes[p].next[1] = -1; nodes[p].next[2] = -1;

    wordCount++;
  }
  if (buf) free(buf);
  return wordCount;
}

// Initialize navigation structure on the nodes
void initNav(NODE* nodes, BYTE dim) {
  BYTE x,y,z;
  BYTE last; // Least recently visited non-empty index
  for (z = 0; z < LEN; z++) {
    for (y = 0; y < LEN; y++) {
      last = -1;
      for (x = 0; x < LEN; x++) {
        // If there is a word present
        if (nodes[pos2(x,y,z,dim)].component != -1) {
          // Set pointer to last word
          nodes[pos2(x,y,z,dim)].prev[dim] = last;
          // If last word existing, set reversed pointer, too
          if (last != -1) {
            nodes[pos2(last,y,z,dim)].next[dim] = x;
          }
          last = x;
        }
      }
    }
  }
}
