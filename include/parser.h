#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H

/**
 * @brief Parses a string into an int if it fails, it exits with 1
 *
 * @param port_string The string to be parsed into an integer
 *
 * @return The port number
 */
int parse_port(char *port_string);

#endif // INCLUDE_PARSER_H
