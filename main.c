#include "main.h"

void usage_msg() {
  fprintf(stderr, "Usage: 3words <word list> <mode>\n");
  fprintf(stderr, "Modes:\n  %s\n    %s\n  %s\n    %s\n  %s\n    %s\n    %s\n  %s\n    %s\n",
                  "components", "Lists the connected components of the word graph",
                  "degrees", "Lists the degrees of the words and their neighbours",
                  "path", "Displays a shortest path between two words in the graph",
                          "Example: 3words <word list> path bus car",
                  "stats", "Displays key figures of the word graph");
}

int main(int argc, char *argv[]) {
  // Usage message
  if (argc < 3) {
    usage_msg();
    return EXIT_FAILURE;
  }

  int mode; // mode of output
  char *a, *b;

  if (strcmp("components",argv[2]) == 0) {
    mode = MODE_COMPONENTS;
  } else if (strcmp("degrees",argv[2]) == 0) {
    mode = MODE_DEGREES;
  } else if (strcmp("path",argv[2]) == 0) {
    mode = MODE_PATH;
  } else if (strcmp("stats",argv[2]) == 0) {
     mode = MODE_STATS;
  } else {
    usage_msg();
  }

  if (mode & MODE_PATH) {
    if (argc < 5 || strlen(argv[3]) < 3 || strlen(argv[4]) < 3) {
      fprintf(stderr, "Please specify two 3-letter words\nExample: 3words path bus car\n");
      return EXIT_FAILURE;
    }
    a = argv[3];
    b = argv[4];
    if (a[0]<'a'||a[0]>'z'||a[1]<'a'||a[1]>'z'||a[2]<'a'||a[2]>'z'||b[0]<'a'||b[0]>'z'||b[1]<'a'||b[1]>'z'||b[2]<'a'||b[2]>'z') {
      fprintf(stderr, "Please only use lower case 3-letter words\nExample: 3words path bus car\n");
      return EXIT_FAILURE;
    }
  }

  // Open file
  FILE *f_input = fopen(argv[1], "r");
  if (!f_input) {
    fprintf(stderr, "File could not be opened: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  NODE nodes[LEN3];
  init(nodes);

  // Read lines
  INT wordCount = readWords(nodes, f_input);
  fclose(f_input);

  // Init navigation structure on the nodes
  initNav(nodes, 0);
  initNav(nodes, 1);
  initNav(nodes, 2);

  INT componentCount = findComponents(nodes, mode & MODE_COMPONENTLIST);

  if (mode & MODE_COMPONENTSTAT) printf("%d components\n", componentCount - 1);

  calcDegrees(nodes, mode & MODE_DEGREESTAT, mode & MODE_DEGREELIST);

  if (mode & MODE_PATH) shortestPath(nodes, a[0]-'a',a[1]-'a',a[2]-'a',b[0]-'a',b[1]-'a',b[2]-'a', TRUE);
}
