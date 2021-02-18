#include <err.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "parser.h"
#include "usage_client.h"

int main(int argc, char *argv[]) {
  int sock_fd, newsock_fd, port_n, cli_len, chars_read;
  char buffer[512] = {0};
  buffer[0] = 'P';
  buffer[1] = 'I';
  buffer[2] = 'N';
  buffer[3] = 'G';
  buffer[4] = '\n';
  struct sockaddr_in serv_addr = {0};

  // Check for arguments and print usage if there is a wrong number of
  // arguments
  usage_client(argc, argv);

  serv_addr.sin_family = AF_INET;
  parse_port(&serv_addr, argv[2]);
  parse_addr(&serv_addr, argv[1]);

  errno = 0;
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    err(errno, "Error: Failed to create socket");
  }

  if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    err(errno, "Error: Failed to connect");
  }

  printf("PING %s 56 bytes of data\n", argv[1]);
  for (uint8_t i = 1; i < 9; i++) {
    struct timespec t0, t1;
    double elapsed;
    int bsent, brecv;

    // Get t0 to calculate time delta
    // NOTE: It is done with the monotonic clock to avoid t1 < t0
    clock_gettime(CLOCK_MONOTONIC, &t0);

    // Send to server and check for errors
    bsent = send(sock_fd, buffer, 8, 0);
    if(bsent == -1) {
      close(sock_fd);
      err(errno, "Errro while writing to socket");
    }

    // Received bytes and check for errors
    brecv = recv(sock_fd, buffer, 512 * sizeof(char), 0);
    if (brecv == -1) {
      close(sock_fd);
      err(errno, "Errro while reading from socket");
    }

    // Get t1 to calculate time delta and the print it
    // NOTE: It is done with the monotonic clock to avoid t1 < t0
    clock_gettime(CLOCK_MONOTONIC, &t1);
    if (t1.tv_sec - t0.tv_sec) {
      printf("%d bytes from %s: time=%lds\n", 8, argv[1], t1.tv_sec - t0.tv_sec );
    } else {
      elapsed = t1.tv_nsec - t0.tv_nsec;
      printf("%d bytes from %s: time=%lfms\n", 8, argv[1], elapsed / 1000);
    }
  }

  close(sock_fd);

  return 0;
}
