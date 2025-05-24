/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:50:32 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/24 16:48:04 by rparodi          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#include "core.hpp"

class User;
class Server
{
private:
	int _port;
	int _serverFd;
	std::string _password;
	PollManager _pollManager;
	std::map<int, User *> _users;

public:
	Server(int port, const std::string &password);
	~Server();
	void start();
	unsigned short int getPort() const;
  std::list<User *> getUsersList() const;
	std::list<Channel *> getChannelsList() const;
	void showInfo() const;
	void printUsers() const;
};
