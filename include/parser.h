#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H

#include <netinet/in.h>

/**
 * @brief Parses a string into an int in network endianess. If it
 *        fails, it exits the program with 1
 *
 * @param port_string The string to be parsed into an integer
 *
 * @return The port number
 */
int parse_port(char *port_string);

/**
 * @brief Parses a string into a sockaddr_in and if it fails, it exits
 *        with 1
 *
 * @param addr      The string to be parsed into a sockaddr_in
 * @out   serv_addr The struct to store the result of the parsed
 *                  string
 *
 * @return The port number
 */
void parse_addr(struct sockaddr_in *serv_addr, char *addr);

#endif // INCLUDE_PARSER_H
