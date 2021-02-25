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
  int sock_fd, newsock_fd, port_n, cli_len, chars_read;
  char buffer[512] = {0};
  struct sockaddr_in serv_addr = {0}, clie_addr = {0};
  socklen_t size = sizeof(clie_addr);

  // Set recv address struct to send back to the client
  clie_addr.sin_family = AF_INET;
  clie_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  clie_addr.sin_port = htons(7654);

  // Check for arguments and print usage if there is a wrong number of
  // arguments
  usage_server(argc, argv);

  // Try to create an IPv4 sockaddr structure from the command line
  // arguments
  serv_addr.sin_family = AF_INET;
  parse_port(&serv_addr, argv[1]);

  // Clear errno and check for socket creation errors
  errno = 0;
  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_fd == -1) {
    err(errno, "Error: Failed to create socket");
  }

  // Try to bind to the specified address
  if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    err(errno, "Error: Failed to connect");
  }

  printf("Listening on port %s\n", argv[1]);

  // Loop until the client closes the connection
  while (1) {
    int brecv, bsent;

    // Receive bytes
    brecv = recvfrom(sock_fd, buffer, 512 * sizeof(char), 0,
                     (struct sockaddr *)&clie_addr, &size);

    // If brecv is -1 something went wrong, free resources and abort
    if (brecv < 0) {
      close(sock_fd);
      err(errno, "Error: Failed to read from connection");
    } else {
      // If brecv is 0, that means that the connection is closed,
      // break out of the loop to keep awaiting to accept new
      // connections
      if (brecv == 0) {
        close(sock_fd);
        printf("[i] The client has closed the connection\n");
        break;
      }
    }

    printf("[i] Received %d bytes\n", brecv);

    // Try send the same that the client sent us
    bsent = sendto(sock_fd, buffer, 8, 0, (struct sockaddr *)&clie_addr, size);
    if (bsent == -1) {
      close(sock_fd);
      err(errno, "Error: Failed to send");
    }
  }

  close(sock_fd);

  return 0;
}
