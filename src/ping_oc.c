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
  parse_port(&serv_addr ,argv[2]);
  parse_addr(&serv_addr, argv[1]);

  return 0;
}
