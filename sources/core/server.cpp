/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:11:07 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/13 11:19:18 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.hpp"
#include <iostream>

/**
 * @brief The default constructor of the Server class.
 */
Server::Server() : _port(0), _password("") {
	if (DEBUG)
		std::cerr << CLR_MAGENTA << "[DEBUG] Thanks to use the constructor with port and password !" << std::endl;
	std::cout << CLR_GREY << "[INFO] Server default constructor called" << CLR_RESET << std::endl;
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
	std::cout << CLR_GREY << "[INFO] Server constructor called" << CLR_RESET << std::endl;
}

/**
 * @brief The default destructor of the Server class.
 */
Server::~Server() {
	std::cout << CLR_GREY << "[INFO] Server destructor called" << CLR_RESET << std::endl;
}
