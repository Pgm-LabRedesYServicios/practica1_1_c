#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

void usage(char *prog_name) {
  fprintf(stderr, "Usage:\n %s <address> <port>\n", prog_name);
}

int main(int argc, char *argv[]) {
  int sock_fd, newsock_fd, port_n, cli_len, chars_read;
  char buffer[512] = {0};
  struct sockaddr_in serv_addr, cli_addr;

  if (argc == 1) {
    fprintf(stderr, "Error: Port number not provided\n");
    usage(argv[0]);
    exit(1);
  }

  if (argc == 0) {
    fprintf(stderr, "Error: No arguments provided\n");
    usage(argv[0]);
    exit(1);
  }

  if (argc > 2) {
    fprintf(stderr, "Error: Too many arguments\n");
    usage(argv[0]);
    exit(1);
  }

  return 0;
}
