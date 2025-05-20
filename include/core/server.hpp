/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:06:56 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/19 23:46:07 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "PollManager.hpp"

class Server {
public:
	Server();
	Server(int port, const std::string &password);
	~Server();

	unsigned short int	getPort() const;
	void				showInfo() const;
	void				setServerFd(int fd);
	void				start();
		
private:
	unsigned short int	_port;
	int					_serverFd;
	std::string			_password;
	PollManager			_poll;
};

