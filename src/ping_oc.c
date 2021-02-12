#include <err.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "parser.h"
#include "usage_client.h"

int main(int argc, char *argv[]) {
  int sock_fd, newsock_fd, port_n, cli_len, chars_read;
  char buffer[512] = {0};
  struct sockaddr_in serv_addr;

  usage_client(argc, argv);

  serv_addr.sin_family = AF_INET;
  parse_port(&serv_addr, argv[2]);
  parse_addr(&serv_addr, argv[1]);

  errno = 0;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    err(errno, "Error: Failed to create socket\n");
  }

  if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    err(errno, "Error: Failed to connect\n");
  }

  return 0;
}
