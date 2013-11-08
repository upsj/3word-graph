#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define LEN 26
#define LEN3 LEN * LEN * LEN

// A single word placed in a 3-dimensional cube (coordinates are letters)
typedef struct NODE { 
  // Component/group indicator for the word
  int component;

  // Distance (char difference) to the next (P)/previous (M) word
  // differing only in the first/second/third letter.
  char aP;
  char aM;
  char bP;
  char bM;
  char cP;
  char cM;
} NODE;

uint32_t pos(int x, int y, int z) {
  return x + LEN * y + LEN * LEN * z;
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
    nodes[pos(a,b,c)].component = 0;
    nodes[pos(a,b,c)].aP = -1;
    nodes[pos(a,b,c)].aM = -1;
    nodes[pos(a,b,c)].bP = -1;
    nodes[pos(a,b,c)].bM = -1;
    nodes[pos(a,b,c)].cP = -1;
    nodes[pos(a,b,c)].cM = -1;
  }

  int x,y,z;
  int last; // Least recently visited non-empty index
  for (z = 0; z < LEN; z++) {
    for (y = 0; y < LEN; y++) {
      last = -1;
      for (x = 0; x < LEN; x++) {
        // If there is a word present
        if (nodes[pos(x,y,z)].component != -1) {
          // Set pointer to last word
          nodes[pos(x,y,z)].aM = last;
          // If last word existing, set reversed pointer, too
          if (last != -1) {
            nodes[pos(last,y,z)].aP = x;
          }
          last = x;
        }
      }
    }
  }

  // same for y and z
  for (z = 0; z < LEN; z++) {
    for (x = 0; x < LEN; x++) {
      last = -1;
      for (y = 0; y < LEN; y++) {
        if (nodes[pos(x,y,z)].component != -1) {
          nodes[pos(x,y,z)].bM = last;
          if (last != -1) {
            nodes[pos(x,last,z)].bP = y;
          }
          last = y;
        }
      }
    }
  }

  for (y = 0; y < LEN; y++) {
    for (x = 0; x < LEN; x++) {
      last = -1;
      for (z = 0; z < LEN; z++) {
        if (nodes[pos(x,y,z)].component != -1) {
          nodes[pos(x,y,z)].cM = last;
          if (last != -1) {
            nodes[pos(x,y,last)].cP = z;
          }
          last = z;
        }
      }
    }
  }

  fclose(f_input);
}
