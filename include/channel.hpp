/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:18:17 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/26 22:54:58 by rparodi          ###   ########.fr       */
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
		std::list<User *> _operators;
		std::list<User *> _users;
		std::list<User *> _invited;
	public:
		// getters
		std::string getName() const;
		std::string getTopic() const;
		User *getOwner() const;
		std::list<User *> getOperators() const;
		std::list<User *> getUsers() const;
		std::list<User *> getInvited() const;
		bool isOperator(User *user) const;
		bool isUserInChannel(User *user) const;

		// setters
		void setTopic(const std::string &topic);
		void addOperator(User *user);
		void addUser(User *user);
		void removeUser(User *user);
		void removeOperator(User *user);
};
