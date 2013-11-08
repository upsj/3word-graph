#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define LEN 26
#define LEN3 LEN * LEN * LEN

// A single word placed in a 3-dimensional cube (coordinates are letters)
typedef struct NODE { 
  // Component/group indicator for the word
  int component;

  // Step size in each dimension to the next/prev word (-1 if not existant)
  char next[3];
  char prev[3];
} NODE;

// Array index for given coordinates
uint32_t pos(int x, int y, int z) {
  return x + LEN * y + LEN * LEN * z;
}

// Array index for given coordinates with permutated x,y,z
uint32_t pos2(int x, int y, int z, char dim) {
  if (dim == 0) {
    return pos(x,y,z);
  } else if (dim == 1) {
    return pos(y,x,z);
  } else if (dim == 2) {
    return pos(z,x,y);
  }
  return -1;
}

// Initialize navigation structure on the nodes
uint32_t initNav(NODE* nodes, char dim) {
  int x,y,z;
  int last; // Least recently visited non-empty index
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

int main(int argc, char *argv[]) {
  // Usage message
  if (argc != 2) {
    printf("Usage: word3components <input file>\n");
    return EXIT_FAILURE;
  }

  // Open file
  FILE *f_input = fopen(argv[1], "r");
  if (!f_input) {
    printf("File could not be opened: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  NODE nodes[LEN3];
  // Initialize nodes
  int i;
  for (i = 0; i < LEN3; i++) {
    nodes[i].component = -1;
  }

  char* buf = malloc(5); // Reading buffer
  size_t buf_size = 5;
  size_t line = 0; // Line counter
  ssize_t read; // Size of last line
  char a,b,c; // Character indices

  // Read lines
  while ((read = getline(&buf, &buf_size, f_input)) != -1) {
    line++;
    // 3 letter words should be in each line
    if (read < 3) {
      printf("Word too short in line %d: %s\n", line, buf);
      continue;
    }

    a = buf[0] - 'a';
    b = buf[1] - 'a';
    c = buf[2] - 'a';
    if (a > 25 || a < 0 || b > 25 || b < 0 || c > 25 || c < 0) {
      printf("Not a lower case character in line %d: %s\n", line, buf);
      continue;
    }

    // Mark node as existing
    int p = pos(a,b,c);
    nodes[p].component = 0;
    nodes[p].prev[0] = -1; nodes[p].prev[1] = -1; nodes[p].prev[2] = -1;
    nodes[p].next[0] = -1; nodes[p].next[1] = -1; nodes[p].next[2] = -1;
  }

  // Init navigation structure on the nodes
  initNav(nodes, 0);
  initNav(nodes, 1);
  initNav(nodes, 2);

  for (i = 0; i < 26; i++) {
    int p = pos(2,0,i);
    a = 'c';
    b = 'a';
    c = i + 'a';
    if (nodes[p].component == -1) {
      printf("%2d %c%c%c: \n", i, a, b, c);
    } else {
      printf("%2d %c%c%c: x %d %d\n", i, a, b, c, nodes[p].next[2], nodes[p].prev[2]);
    }
  }

  fclose(f_input);
}
