/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:18:17 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/21 14:36:38 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "user.hpp"
#include "server.hpp"
#include <string>
#include <list>

class Channel {
	public:
		Channel(const std::string &name, User *owner, size_t maxUsers, bool needInvite);
		~Channel();
		// getters
		std::string getName() const;
		std::string getTopic() const;
		size_t getMaxUsers() const;
		User *getOwner() const;
		std::list<User *>& getOperators();
		std::list<User *>& getUsers();
		std::list<User *> getInvited() const;
		std::string getPassword() const;
		bool isOperator(User *user) const;
		bool isUserInChannel(User *user) const;
		bool getNeedInvite() const;
		bool getProtectTopic() const;

		// setters
		void setProtectTopic(bool toSet);
		void setMaxUser(size_t args);
		void setNeedInvite(bool toSet);
		void setTopic(const std::string &topic);
		void setPassword(const std::string &newPass);
		void addOperator(User *user);
		void addUser(User *user);
		void addInvited(User *user);
		bool isInvited(User *user) const;
		void removeUser(User *user);
		void removeOperator(User *user);
		void setBotChannel(bool isBot);
		bool getBotChannel() const;
		
		// utility functions
		void sendAllClientInAChannel(const std::string &toSend, User *exclude = NULL);

	private:
		std::string _name;
		User *_owner;
		std::string _password;
		size_t _maxUsers;
		bool _needInvite;
		bool _protectTopic;
		std::string _topic;
		std::list<User *> _operators;
		std::list<User *> _users;
		std::list<User *> _invited;
		bool _botChannel;
};


