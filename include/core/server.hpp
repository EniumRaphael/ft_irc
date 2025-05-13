/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:06:56 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/13 12:54:02 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Server {
	private:
		unsigned short int _port;
		std::string _password;
	public:
		Server();
		Server(int port, const std::string &password);
		~Server();
		void showInfo() const;
		unsigned short int getPort() const;
};
