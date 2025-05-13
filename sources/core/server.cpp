/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:11:07 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/13 13:05:07 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.hpp"
#include "core.hpp"
#include <iostream>

/**
 * @brief The default constructor of the Server class.
 */
Server::Server() : _port(0), _password("") {
	if (DEBUG)
		std::cerr << CLR_MAGENTA << "Debug: Thanks to use the constructor with port and password !" << std::endl;
	std::cout << CLR_GREY << "Info: Server default constructor called" << CLR_RESET << std::endl;
}

/**
 * @brief The constructor of the Server class.
 *
 * @param port The port given by the user (argv[1])
 * @param password The password given by the user (argv[2])
 *
 * @note Thanks to check the port / password before give them to the constructor.
 */
Server::Server(int port, const std::string &password) : _port(port), _password(password) {
	std::cout << CLR_GREY << "Info: Server constructor called" << CLR_RESET << std::endl;
}

/**
 * @brief The default destructor of the Server class.
 */
Server::~Server() {
	std::cout << CLR_GREY << "Info: Server destructor called" << CLR_RESET << std::endl;
}

void Server::showInfo() const {
	std::cout << std::endl;
	std::cout << CLR_BLUE << "IRCSettings:" << CLR_RESET << std::endl;
	std::cout << CLR_BLUE << "\t- Port:\t\t" << CLR_GOLD << this->_port << CLR_RESET << std::endl;
	std::cout << CLR_BLUE << "\t- Password:\t" << CLR_GOLD << this->_password << CLR_RESET << std::endl;

}

/**
 * @brief The getter of the port.
 *
 * @return the port of the server
 */
unsigned short int Server::getPort() const {
	return this->_port;
}
