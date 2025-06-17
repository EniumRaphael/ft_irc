/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:50:32 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/18 01:09:21 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <list>
#include <map>
#include "core.hpp"
#include "channel.hpp"
#include "user.hpp"
#include "logs.hpp"

class User;
class Channel;
class Server

{
private:
	int _port;
	int _serverFd;
	std::string _password;
	PollManager _pollManager;
	std::map<int, User *> _users;
	std::list<Channel *> _channels;

public:
	Server(int port, const std::string &password);
	~Server();
	void start();
	std::list<Channel *>& getChannelsList();
	std::list<User *> getUsersList() const;
	PollManager& getPollManager();
	unsigned short int getPort() const;
	std::string getPassword() const;
	void showInfo() const;
	void printUsers() const;
	void disconnectClient(int fd);
};
