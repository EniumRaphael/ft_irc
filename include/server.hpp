/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:50:32 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/24 16:48:04 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "PollManager.hpp"
#include <list>
#include "user.hpp"
#include "channel.hpp"

class Server {
	private:
		int _port;
		int _serverFd;
		std::string _password;
		PollManager _pollManager;
	public:
		Server(int port, const std::string &password);
		~Server();
		void start();
		std::list<User *> getUsersList() const;
		std::list<Channel *> getChannelsList() const;
		unsigned short int getPort() const;
		void showInfo() const;
};
