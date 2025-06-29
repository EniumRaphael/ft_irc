/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:43:24 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/23 14:55:34 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"
#include <iostream>
#include <algorithm>

Channel::Channel(const std::string &name, User *owner, size_t maxUsers, bool needInvite) : _name(name), _owner(owner), _maxUsers(maxUsers), _needInvite(needInvite) {
	this->_protectTopic = false;
	if (BONUS)
		this->_botChannel = true;
	else
		this->_botChannel = false;
	this->_maxUsers = ~0;
	this->_topic = "";
}

Channel::~Channel() {
	_users.clear();
	_operators.clear();
	_invited.clear();
}

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
std::list<User *>& Channel::getUsers() {
	return this->_users;
}

/**
 * @brief Get the list of the Operators in the channel
 *
 * @return list of Operators in the channel
 */
std::list<User *>& Channel::getOperators() {
	return this->_operators;
}

/**
 * @brief Get the password of the channel
 *
 * @return string with the password
 */
std::string Channel::getPassword() const {
	return this->_password;
}

/**
 * @brief Get the max user allowd to be in the channel
 *
 * @return size_t max user
 */
size_t Channel::getMaxUsers() const {
	return this->_maxUsers;
}

/**
 * @brief Get if an invitation is needed for this channel
 *
 * @return the boolean to check if an invite is needed for the channel
 */
bool Channel::getNeedInvite() const {
	return this->_needInvite;
}

/**
 * @brief Setter got the NeedInvite channel
 *
 * @param toSet The new value for need Invite
 */
void Channel::setNeedInvite(bool toSet) {
	this->_needInvite = toSet;
}

/**
 * @brief Setter for the Max User for the channel
 *
 * @param arg the new number (integer / long)
 */
void Channel::setMaxUser(size_t arg) {
	this->_maxUsers = arg;
}

/**
 * @brief Get the list of the Invited in the channel
 *
 * @return list of Invited in the channel
 */
std::list<User *> Channel::getInvited() const {
	return this->_invited;
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

bool Channel::getProtectTopic() const {
	return this->_protectTopic;
}

void Channel::setProtectTopic(bool toSet) {
	this->_protectTopic = toSet;
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
 * @brief Setter for the Channel's password
 *
 * @param newPass the new password to set
 */
void Channel::setPassword(const std::string &newPass) {
	this->_password = newPass;
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
	if (!user) {
		std::cerr << "Error: Attempt to add a null user to the channel " << this->_name << std::endl;
		DEBUG_MSG("Attempt to add a null user to the channel " << this->_name);
		return;
	}
	if (this->isUserInChannel(user) == false) {
		DEBUG_MSG("Adding user " << user->getName() << " to channel " << this->_name);
		this->_users.push_back(user);
	}
	else {
		DEBUG_MSG("User " << user->getName() << " is already in channel " << this->_name);
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

void Channel::sendAllClientInAChannel(const std::string &toSend, User *exclude) {
	for (std::list<User *>::iterator it = _users.begin(); it != _users.end(); ++it) {
		if (*it != exclude)
			(*it)->appendToWriteBuffer(toSend);
	}
}

void Channel::addInvited(User *user) {
	if (user && !isInvited(user))
		_invited.push_back(user);
}

bool Channel::isInvited(User *user) const {
	if (user)
	{
		if (std::find(_invited.begin(), _invited.end(), user) != _invited.end())
			return true;
	}
	std::cerr << user->getName() << " is not invited to the channel " << this->_name << std::endl;
	return false;
}

void Channel::setBotChannel(bool isBot) { _botChannel = isBot; }

bool Channel::getBotChannel() const { return _botChannel; }