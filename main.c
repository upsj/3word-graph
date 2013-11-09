#include "main.h"

NODE nodes[LEN3];
int mode; // mode of processing: short stats, component list, 

int main(int argc, char *argv[]) {
  // Usage message
  if (argc < 2) {
    fprintf(stderr, "Usage: 3words [options] <input file>\n");
    return EXIT_FAILURE;
  }

  // Open file
  FILE *f_input = fopen(argv[1], "r");
  if (!f_input) {
    fprintf(stderr, "File could not be opened: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  init(nodes);

  // Read lines
  INT wordCount = readWords(nodes, f_input);
  fclose(f_input);

  // Init navigation structure on the nodes
  initNav(nodes, 0);
  initNav(nodes, 1);
  initNav(nodes, 2);

  INT componentCount = findComponents(nodes, 1);

  printf("%d components\n", componentCount - 1);

  calcDegrees(nodes, TRUE, TRUE);
}
