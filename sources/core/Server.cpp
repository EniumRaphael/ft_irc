/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:11:07 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/21 21:50:03 by omoudni          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
    if (_serverFd != -1) {
        close(_serverFd);
    }
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
    std::vector<int> newClients;
    std::vector<int> disconnected;
    std::vector<std::pair<int, std::string> > readyClients;
    while (true)
    {
        newClients.clear();
        disconnected.clear();
        readyClients.clear();
        _pollManager.pollLoop(_serverFd, newClients, disconnected, readyClients);

        // Handle new clients
        for (size_t i = 0; i < newClients.size(); ++i)
            _users[newClients[i]] = new User(newClients[i]);
        // Handle disconnected clients
        for (size_t i = 0; i < disconnected.size(); ++i)
        {
            delete _users[disconnected[i]];
            _users.erase(disconnected[i]);
        }
        for (size_t i = 0; i < readyClients.size(); ++i)
        {
            int fd = readyClients[i].first;
            const std::string &data = readyClients[i].second;
            if (_users.count(fd))
            {
                _users[fd]->appendToReadBuffer(data);
                //print users
                std::cout << "User " << fd << " is registered: " << _users[fd]->isRegistered() << std::endl;
                std::cout << "Received data from fd " << fd << ": " << data << std::endl;
                std::string cmd;
                while (!(cmd = _users[fd]->extractFullCommand()).empty())
                {
                    // This prints every command/message received from any client
                    std::cout << "Client " << fd << " says: " << cmd << std::endl;
                    
                }
            }
        }

        // Optionally: handle server shutdown, signals, etc.
    }
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

