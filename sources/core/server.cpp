/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:11:07 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/14 23:32:21 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.hpp"
#include "server.hpp"
#include "core.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
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
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		std::cerr << CLR_RED << "Error: Failed to create socket" << CLR_RESET << std::endl;
		return;
	}
	setServerFd(fd);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(this->_port);
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		std::cerr << CLR_RED << "Error: Failed to bind socket" << CLR_RESET << std::endl;
		close(server_fd);
		return;
	}
	if (listen(server_fd, 5) == -1) {
		std::cerr << CLR_RED << "Error: Failed to listen on socket" << CLR_RESET << std::endl;
		close(server_fd);
		return;
	}
	std::cout << CLR_GREEN << "Server started on port " << this->_port << CLR_RESET << std::endl;
	std::cout << CLR_GREEN << "Waiting for clients..." << CLR_RESET << std::endl;
	while (true) {
		int client_fd = accept(server_fd, NULL, NULL);
		if (client_fd == -1) {
			std::cerr << CLR_RED << "Error: Failed to accept client" << CLR_RESET << std::endl;
			continue;
		}
		std::cout << CLR_GREEN << "Client connected" << CLR_RESET << std::endl;
		close(client_fd);
	}
	close(server_fd);
	std::cout << CLR_GREEN << "Server stopped" << CLR_RESET << std::endl;
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

void Server::setServerFd(int fd) {
	this->server_fd = fd;
}


