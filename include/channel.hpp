/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:18:17 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/17 17:52:19 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "user.hpp"
#include <string>
#include <list>

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::string _topic;
		User *_owner;
		bool _needInvite;
		size_t _maxUsers;
		std::list<User *> _operators;
		std::list<User *> _users;
		std::list<User *> _invited;
	public:
		// getters
		std::string getName() const;
		std::string getTopic() const;
		size_t getMaxUsers() const;
		User *getOwner() const;
		std::list<User *> getOperators() const;
		std::list<User *> getUsers() const;
		std::list<User *> getInvited() const;
		std::string getPassword() const;
		bool isOperator(User *user) const;
		bool isUserInChannel(User *user) const;
		bool getNeedInvite() const;

		// setters
		void setMaxUser(size_t args);
		void setNeedInvite(bool toSet);
		void setTopic(const std::string &topic);
		void setPassword(const std::string &newPass);
		void addOperator(User *user);
		void addUser(User *user);
		void removeUser(User *user);
		void removeOperator(User *user);
};
