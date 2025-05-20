/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:29:56 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/15 12:38:56 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logs.hpp"

void print_debug(const char *str, const char *file, int line)
{
	if (DEBUG)
		std::cout << CLR_CYAN << "\tDebug: " << str << "(" << file << ":" << line << ")" << CLR_RESET << std::endl;
}

void print_error(const char *str, const char *file, int line)
{
	std::cerr << CLR_RED << "\tError: " << str << "(" << file << ":" << line << ")" << CLR_RESET << std::endl;
}

void print_warning(const char *str, const char *file, int line)
{
	std::cerr << CLR_YELLOW << "\tWarning: " << str << "(" << file << ":" << line << ")" << CLR_RESET << std::endl;
}

void print_info(const char *str, const char *file, int line)
{
	std::cout << CLR_GREY << "\tInfo: " << str << "(" << file << ":" << line << ")" << CLR_RESET << std::endl;
}

void print_success(const char *str, const char *file, int line)
{
	std::cout << CLR_GREEN << "\tSuccess: " << str << "(" << file << ":" << line << ")" << CLR_RESET << std::endl;
}
