/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:57:49 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/19 02:22:55 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "PollManager.hpp"

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
		std::string _realname;
		std::string _ipAdress;
		
		bool _hasNick;
		bool _hasUser;
		bool _hasPass;
		bool _passReceived;
		bool _passIsValid;

		PollManager& _poll;
	
	public:
		User(short unsigned fd, PollManager& poll);
		short unsigned int getFd() const;
		bool isReadyToSend() const;
		bool isRegistered() const;
		std::string getName() const;
		std::string extractFullCommand();
		void setRegistered();
		void appendToReadBuffer(const std::string &data);
		void appendToWriteBuffer(const std::string &data);
		void checkRegistration();
		void resolveHostInfo();
		
		// setters and getters
		void setNickname(const std::string &nickname);
		void setUsername(const std::string &username);
		void setRealname(const std::string &realname);
		std::string getUsername(void) const;
		std::string getRealname(void) const;
		void setHasNick(bool value);
		void setHasUser(bool value);
		void setHasPass(bool value);
		void setPassReceived(bool value);
		void setPassIsValid(bool value);
		bool getHasPass() const;
		std::string getNickname() const;
		const std::string& getHostname() const;
		const std::string& getIpAddress() const;
		void setHostname(const std::string &hostname);
		void setIpAddress(const std::string &ip);

		bool hasDataToSend() const;
		std::string getWriteBuffer() const;
		void clearWriteBuffer();
		void consumeWriteBuffer(size_t len);

		std::string getPrefix() const;
};
