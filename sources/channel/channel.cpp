/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:43:24 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/26 18:10:43 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"
#include <iostream>

/**
 * @brief Get the name of the channel
 *
 * @return string with the channel name
 */
std::string Channel::getName() const {
	return this->_name;
}

/**
 * @brief Get the topic of the channel
 *
* @return string with the channel topic
 */
std::string Channel::getTopic() const {
	return this->_topic;
}

/**
 * @brief Get the owner of the channel
 *
 * @return User which own the channel
 */
User *Channel::getOwner() const {
	return this->_owner;
}

/**
 * @brief Get the list of the Users in the channel
 *
 * @return list of Users in the channel
 */
std::list<User *> Channel::getUsers() const {
	return this->_users;
}

/**
 * @brief Get the list of the Operators in the channel
 *
 * @return list of Operators in the channel
 */
std::list<User *> Channel::getOperators() const {
	return this->_operators;
}

/**
 * @brief Check if the user is an operator
 *
 * @param user to check the status
 * @return true if the user is an operator, false otherwise
 */
bool Channel::isOperator(User *user) const {
	for (std::list<User *>::const_iterator it = this->_operators.begin(); it != this->_operators.end(); ++it) {
		if (*it == user) {
			return true;
		}
	}
	return false;
}

/**
 * @brief Check if the user is in the channel
 *
 * @param user to check the status
 * @return true if the user is in the channel, false otherwise
 */
bool Channel::isUserInChannel(User *user) const {
	for (std::list<User *>::const_iterator it = this->_users.begin(); it != this->_users.end(); ++it) {
		if (*it == user) {
			return true;
		}
	}
	return false;
}

/**
 * @brief Setter for the topic of the channel
 *
 * @param topic new topic to set
 */
void Channel::setTopic(const std::string &topic) {
	this->_topic = topic;
}

/**
 * @brief Setter to set a new operator in the channel
 *
 * @param user to set as operator
 */
void Channel::addOperator(User *user) {
	if (this->isOperator(user) == false) {
		this->_operators.push_back(user);
	}
	else {
		std::cerr << user->getName() << " is already an operator in the channel " << this->_name << std::endl;
	}
}

/**
 * @brief Setter to set a new user in the channel
 *
 * @param user to add in the channel
 */
void Channel::addUser(User *user) {
	if (this->isUserInChannel(user) == false) {
		this->_users.push_back(user);
	}
	else {
		std::cerr << user->getName() << " is already in the channel " << this->_name << std::endl;
	}
}

/**
 * @brief Setter to remove a user from the channel
 *
 * @param user to remove from the channel
 */
void Channel::removeUser(User *user) {
	if (this->isUserInChannel(user) == true) {
		this->_users.remove(user);
	}
	else {
		std::cerr << user->getName() << " is not in the channel " << this->_name << std::endl;
	}
}

/**
 * @brief Setter to remove an operator from the channel
 *
 * @param user to remove from the channel
 */
void Channel::removeOperator(User *user) {
	if (this->isOperator(user) == true) {
		this->_operators.remove(user);
	}
	else {
		std::cerr << user->getName() << " is not an operator in the channel " << this->_name << std::endl;
	}
}

