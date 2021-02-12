#include <parser.h>

#include <err.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>

/**
 * @brief Parses a string into an int if it fails, it exits with 1
 *
 * @param port_string The string to be parsed into an integer
 *
 * @return The port number
 */
int parse_port(char *port_string) {
  int res;
  char* invalid_addr;

  errno = 0;
  res = strtol(port_string, &invalid_addr, 10);
  if (errno) {
    err(errno, "Ill-formed port string");
  }

  res = htons(res);

  return res;
}
