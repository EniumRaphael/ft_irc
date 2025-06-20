/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:11:07 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/20 19:19:42 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.hpp"
#include "server.hpp"
#include "commands.hpp"
#include "core.hpp"
#include "PollManager.hpp"
#include "logs.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sstream>

/**
 * @brief The constructor of the Server class.
 *
 * @param port The port given by the user (argv[1])
 * @param password The password given by the user (argv[2])
 *
 * @note Thanks to check the port / password before give them to the constructor.
 */
Server::Server(int port, const std::string &password) : _port(port), _password(password)
{
    std::cout << CLR_GREY << "Info: Server constructor called" << CLR_RESET << std::endl;
}

/**
 * @brief The default destructor of the Server class.
 */
Server::~Server()
{
    std::cout << CLR_GREY << "Info: Server destructor called" << CLR_RESET << std::endl;
    if (_serverFd != -1)
    {
        close(_serverFd);
    }
}

std::vector<std::string> splitLines(const std::string& input);

void Server::start()
{
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

    if (bind(_serverFd, (sockaddr *)&addr, sizeof(addr)) == -1 ||
        listen(_serverFd, 10) == -1) {
        std::cerr << "Erreur bind/listen" << std::endl;
        close(_serverFd);
        return;
    }

    std::cout << "Serveur lancé sur le port " << _port << std::endl;

    _pollManager.setServerFd(_serverFd);
    std::vector<int> newClients;
    std::vector<int> disconnected;
    std::vector<std::pair<int, std::string > > readyClients;
    std::vector<int> readyToWrite;

    while (true) {
        printUsers();

        newClients.clear();
        disconnected.clear();
        readyClients.clear();
        readyToWrite.clear();

        _pollManager.pollLoop(_serverFd, newClients, disconnected, readyClients, readyToWrite);

        for (size_t i = 0; i < newClients.size(); ++i) {
            _users[newClients[i]] = new User(newClients[i], _pollManager);
        }

        for (size_t i = 0; i < disconnected.size(); ++i) {
            disconnectClient(disconnected[i]);
        }

        for (size_t i = 0; i < readyClients.size(); ++i) {
            int fd = readyClients[i].first;
            const std::string &data = readyClients[i].second;

            if (_users.count(fd)) {
                _users[fd]->appendToReadBuffer(data);
                std::string rawCmd;

                while (!(rawCmd = _users[fd]->extractFullCommand()).empty()) {
                    std::vector<std::string> lines = splitLines(rawCmd);
                    for (size_t i = 0; i < lines.size(); ++i) {
                        std::cout << "Client " << fd << " says: " << lines[i] << std::endl;
                        cmd::dispatch(_users[fd], NULL, this, lines[i]);
                    }
                }
            }
        }

        for (size_t i = 0; i < readyToWrite.size(); ++i) {
            int fd = readyToWrite[i];
            if (_users.count(fd)) {
                std::string writeBuffer = _users[fd]->getWriteBuffer();
                if (!writeBuffer.empty()) {
                    ssize_t bytesSent = send(fd, writeBuffer.c_str(), writeBuffer.size(), MSG_NOSIGNAL);
                    if (bytesSent < 0) {
                        std::cerr << "Erreur send sur fd " << fd << std::endl;
                        disconnectClient(fd);
                    } else {
                            _users[fd]->clearWriteBuffer();
                        // _users[fd]->consumeWriteBuffer(bytesSent);
                        // if (_users[fd]->getWriteBuffer().empty())
                            _pollManager.setWritable(fd, false);
                    }
                }
            }
        }

        std::cout << "Poll loop finished" << std::endl;
    }

    close(_serverFd);
}

/**
 * @brief Show the server settings.
 *
 * @note This function is used to show the server settings.
 *       It is used for debug purpose.
 */

void Server::showInfo() const
{
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
unsigned short int Server::getPort() const { return this->_port; }

void Server::printUsers() const
{
    std::cout << "Connected users:" << std::endl;
    for (std::map<int, User *>::const_iterator it = _users.begin(); it != _users.end(); ++it)
    {
        std::cout << "User fd: " << it->first << std::endl;
        std::cout << "Username: " << it->second->getUsername() << std::endl;
        std::cout << "Nickname: " << it->second->getNickname() << std::endl;
        std::cout << "Realname: " <<  it->second->getRealname() << std::endl;
        std::cout << "hostname: " << it->second->getHostname() << std::endl;
        std::cout << "IP Address: " << it->second->getIpAddress() << std::endl;
        std::cout << "Registered: " << (it->second->isRegistered() ? "Yes" : "No") << std::endl;
        std::cout << "Prefix: " << it->second->getPrefix() << std::endl;
        std::cout << "----------------------------------------" << std::endl;

    }
}

/**
 * @brief The getter for the password
 *
 * @return the password of the server
 */
std::string Server::getPassword() const { return this->_password; }

std::list<User *> Server::getUsersList() const {
	std::list<User*> userList;
	for (std::map<int, User*>::const_iterator it = _users.begin(); it != _users.end(); ++it) {
		userList.push_back(it->second);
	}
	return userList;
}

std::list<Channel *>& Server::getChannelsList() {
	return this->_channels;
}

std::vector<std::string> splitLines(const std::string& input) {
	std::vector<std::string> lines;
	std::istringstream stream(input);
	std::string line;

	while (std::getline(stream, line)) {
		if (!line.empty() && line[line.length() - 1] == '\r')
			line.erase(line.length() - 1); // retirer le \r final
		lines.push_back(line);
	}
	return lines;
}

void Server::disconnectClient(int fd) {
	User *user = _users[fd];
	for (std::list<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		(*it)->removeUser(user);

	delete user;
	_users.erase(fd);
}

PollManager& Server::getPollManager() { return _pollManager; }