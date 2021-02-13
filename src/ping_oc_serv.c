#include <err.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "parser.h"
#include "usage_server.h"

int main(int argc, char *argv[]) {
  int sock_fd, newsock_fd, port_n, cli_len, chars_read, conn;
  char buffer[512] = {0};
  struct sockaddr_in serv_addr = {0}, clie_addr = {0};

  usage_server(argc, argv);

  // TODO: Find a way to resolve an url to IPv4 addr

  serv_addr.sin_family = AF_INET;
  parse_port(&serv_addr, argv[1]);

  errno = 0;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    err(errno, "Error: Failed to create socket");
  }

  if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    err(errno, "Error: Failed to connect");
  }

  listen(sock_fd, 0);

  printf("Listening on port %s\n", argv[1]);

  errno = 0;
  while((conn = accept(sock_fd, (struct sockaddr*)&clie_addr, NULL))) {
    if(errno) {
      int e = errno;
      close(sock_fd);
      err(e, "Error: Failed to accept connection");
    }

    int ret = 1;
    while (ret) {
      // TODO: Implement timeout
      ret = recv(sock_fd, buffer, 512 * sizeof(char), 0);
      printf("[i] Received %d bytes\n", ret);
      if(ret < 0) {
        close(sock_fd);
        err(errno, "Error: Failed to read from connection");
      }

      send(sock_fd, buffer, 8, 0);
    }
  }

  close(sock_fd);

  return 0;
}
