#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int parse_port(char *port_string) {
  int res;
  char *invalid_addr;

  errno = 0;
  res = strtol(port_string, &invalid_addr, 10);
  if (errno) {
    err(errno, "Ill-formed port string");
  }

  res = htons(res);

  return res;
}

void parse_addr(struct sockaddr_in *serv_addr, char *addr) {
  int res;

  // Clear errno since inet_pton might set it
  errno = 0;
  res = inet_pton(AF_INET, addr, &serv_addr->sin_addr);

  switch (res) {
  case 1: {
    // Valid network address
    return;
  }

  case 0: {
    // The address provided is not valid IPv4
    fprintf(stderr, "Error: The address: %s is invalid for IPv4\n", addr);
    exit(1);

    break;
  }

  case -1: {
    // This should never happen since we are providing AF_INET
    err(errno, "This should not happen");
  }

  default: {
    fprintf(stderr, "Error: something went wrong when parsing %s to an IPv4 address\n", addr);
    exit(1);
  }
  }
}
