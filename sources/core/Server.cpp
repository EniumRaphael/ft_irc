/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:11:07 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/19 23:58:53 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.hpp"
#include "server.hpp"
#include "core.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

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


void Server::start() {
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverFd == -1) {
        std::cerr << "Erreur socket" << std::endl;
        return;
    }

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(_port);

    if (bind(_serverFd, (sockaddr*)&addr, sizeof(addr)) == -1 ||
        listen(_serverFd, 10) == -1) {
        std::cerr << "Erreur bind/listen" << std::endl;
        close(_serverFd);
        return;
    }

    std::cout << "Serveur lancé sur le port " << _port << std::endl;

    _poll.pollLoop(_serverFd);
    close(_serverFd);
}

/**
 * @brief Show the server settings.
 *
 * @note This function is used to show the server settings.
 *       It is used for debug purpose.
 */

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

