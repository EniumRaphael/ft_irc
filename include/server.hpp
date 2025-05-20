/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:50:32 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/20 21:53:29 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "PollManager.hpp"

class Server {
	private:
		int _port;
		int _server_fd;
		std::string _password;
		PollManager _poll_manager;
	public:
		Server(int port, const std::string &password);
		~Server();
		void start();
		int getPort() const;
		void showInfo() const;
};
