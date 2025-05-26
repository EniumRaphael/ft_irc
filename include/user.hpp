/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:57:49 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/26 18:10:24 by rparodi          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#include <string>

class User
{
	private:
		short unsigned int _fd;
		bool _registered;
		std::string _nickname;
		std::string _hostname;
		std::string _read_buffer;
		std::string _write_buffer;
		std::string _username;
		bool _hasNick;
		bool _hasUser;
	
	public:
		User(short unsigned fd);
		short unsigned int getFd() const;
		bool isReadyToSend() const;
		bool isRegistered() const;
		std::string getName() const;
		std::string extractFullCommand();
		void appendToReadBuffer(const std::string &data);
		void appendToWriteBuffer(const std::string &data);
		void setNickname(const std::string &nickname);
		void setUsername(const std::string &username);
		void checkRegistration();
};
