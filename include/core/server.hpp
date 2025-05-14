/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:06:56 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/14 23:23:13 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Server {
	private:
		unsigned short int _port;
		std::string _password;
		int server_fd;
	public:
		Server();
		Server(int port, const std::string &password);
		~Server();
		void showInfo() const;
		unsigned short int getPort() const;
		void setServerFd(int fd);
		void start();
};
