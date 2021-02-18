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
  int sock_fd, newsock_fd, port_n, cli_len, chars_read, conn = 0;
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

  while (conn != -1) {
    errno = 0;
    cli_len = sizeof(clie_addr);
    conn = accept(sock_fd,
                  (struct sockaddr *)&clie_addr,
                  (unsigned int *)&cli_len);

    if (conn == -1) {
      int e = errno;
      close(sock_fd);
      err(e, "Error: Failed to accept connection");
    }
    printf("[i] A client has successfully established a connection\n");

    while (1) {
      int brecv, bsent;

      // TODO: Implement timeout
      brecv = recv(conn, buffer, 512 * sizeof(char), 0);
      if (brecv < 0) {
        close(conn);
        close(sock_fd);
        err(errno, "Error: Failed to read from connection");
      } else {
        if (brecv == 0) {
          close(conn);
          printf("[i] The client has closed the connection\n");
          break;
        }
      }

      printf("[i] Received %d bytes\n", brecv);

      bsent = send(conn, buffer, 8, 0);
      if (bsent == -1) {
        close(conn);
        close(sock_fd);
        err(errno, "Error: Failed to send");
      }
    }
  }

  close(sock_fd);

  return 0;
}
