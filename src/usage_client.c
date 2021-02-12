#include "usage_client.h"

#include <stdio.h>
#include <stdlib.h>

static void usage(char *prog_name) {
  fprintf(stderr, "Usage:\n\t%s <address> <port>\n", prog_name);
}

void usage_client(int argc, char **argv) {
  if (argc == 2) {
    fprintf(stderr, "Error: Port number not provided\n\n");
    usage(argv[0]);
    exit(1);
  }

  if (argc == 1) {
    fprintf(stderr, "Error: No arguments provided\n\n");
    usage(argv[0]);
    exit(1);
  }

  if (argc > 3) {
    fprintf(stderr, "Error: Too many arguments\n\n");
    usage(argv[0]);
    exit(1);
  }
}
