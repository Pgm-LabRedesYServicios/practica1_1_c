#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H

#include <netinet/in.h>

/**
 * @brief Parses a string into an int in network endianess. If it
 *        fails, it exits the program with 1
 *
 * @param port_string The string to be parsed into an integer
 * @out   serv_addr   The struct to store the result of the parsed
 *                    string
 */
void parse_port(struct sockaddr_in *serv_addr, char *port_string);

/**
 * @brief Parses a string into a valid IPv4 address and if it fails,
 * it exits with 1
 *
 * @param addr      The string to be parsed into a sockaddr_in
 * @out   serv_addr The struct to store the result of the parsed
 *                  string
 */
void parse_addr(struct sockaddr_in *serv_addr, char *addr);

#endif // INCLUDE_PARSER_H
