/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:57:49 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/16 18:36:01 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		bool _hasPass;
		bool _passReceived;
		bool _passIsValid;
	
	public:
		User(short unsigned fd);
		short unsigned int getFd() const;
		bool isReadyToSend() const;
		bool isRegistered() const;
		std::string getName() const;
		std::string extractFullCommand();
		void setRegistered();
		void appendToReadBuffer(const std::string &data);
		void appendToWriteBuffer(const std::string &data);
		void setNickname(const std::string &nickname);
		void setUsername(const std::string &username);
		void checkRegistration();

		// setters and getters
		void setHasNick(bool value);
		void setHasUser(bool value);
		void setHasPass(bool value);
		void setPassReceived(bool value);
		void setPassIsValid(bool value);
		bool getHasPass() const;
		std::string getNickname() const;

		bool hasDataToSend() const;
		std::string getWriteBuffer() const;
		void clearWriteBuffer();

		std::string getPrefix() const;
};
