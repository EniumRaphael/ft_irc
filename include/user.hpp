/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:57:49 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/20 19:17:53 by sben-tay         ###   ########.fr       */
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
		void appendToReadBuffer(const std::string &data);
		void appendToWriteBuffer(const std::string &data);
		std::string extractFullCommand();
		void checkRegistration();
		void resolveHostInfo();
		
		// setters and getters
		void setRegistered();
		void setNickname(const std::string &nickname);
		void setUsername(const std::string &username);
		void setRealname(const std::string &realname);
		void setHasNick(bool value);
		void setHasUser(bool value);
		void setHasPass(bool value);
		void setPassReceived(bool value);
		void setPassIsValid(bool value);
		void setHostname(const std::string &hostname);
		void setIpAddress(const std::string &ip);
		const std::string getUsername(void) const;
		const std::string getRealname(void) const;
		const std::string getNickname() const;
		const std::string getWriteBuffer() const;
		const std::string& getHostname() const;
		const std::string& getIpAddress() const;
		const std::string getName() const;
		const std::string getPrefix() const;
		
		bool hasDataToSend() const;
		bool getHasPass() const;
		bool isReadyToSend() const;
		bool isRegistered() const;
		
		void clearWriteBuffer();
		void consumeWriteBuffer(size_t len);

};
