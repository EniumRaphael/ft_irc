/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:25:04 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/13 14:20:47 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.hpp"
#include <cerrno>
#include <cstdlib>
#include <iostream>

/**
 * @brief function to check if the port is valid
 *
 * @param input input given bu the user
 * @return value between 1 and 65535 if valid, 0 if not (on unsigned 16 bits)
 */
unsigned short int valid_port(char *input)
{
	if (input == NULL)
		return (0);
	for (size_t i = 0; input[i]; i++) {
		if (!isdigit(input[i])) {
			if (DEBUG)
				std::cerr << LOG << CLR_RED << "Error: Not only number in port: " << input << std::endl;
			return (0);
		}
	}
	errno = 0;
	int port = strtol(input, NULL, 10);
	if (errno == ERANGE) {
		if (DEBUG)
			std::cerr << LOG << CLR_RED << "Error: Port out of range: " << input << std::endl;
		return (0);
	}
	if (port < 1 || port > 65535)
		return (0);
	return (port);
}
