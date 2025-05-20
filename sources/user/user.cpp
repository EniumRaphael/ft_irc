/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:03:36 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/20 22:15:14 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

/**
 * @brief Getter for the fd of the user
 *
 * @return the actual fd of the user
 */
int User::getFd() const {
	return this->_fd;
}

/**
 * @brief Getter for the nickname of the user
 *
 * @return the actual nickname of the user
 */
std::string User::getNickname() const {
	return this->_nickname;
}

/**
 * @brief Setter for the nickname of the user (also checker)
 *
 * @param nickname the nickname given to set to the user
 */
void User::setNickname(const std::string &nickname) {
	if (nickname.empty()) {
		throw std::invalid_argument("Nickname cannot be empty");
	} else if (nickname == "anonymous") {
		throw std::invalid_argument("Nickname cannot be 'anonymous'");
	} else if (nickname.length() > 9) {
		throw std::length_error("Nickname is too long");
	} else if (nickname == this->_nickname) {
		throw std::invalid_argument("The nickname is the same");
	} else {
		this->_nickname = nickname;
	}
}

/**
 * @brief Getter for the state of the user
 *
 * @return true if the user is registered, false otherwise
 */
bool User::isRegistered() const {
	return this->_registered;
}
void User::appendToReadBuffer(const std::string &data) {
	std::cerr << CLR_RED << "Error: Method not found (" << __FILE_NAME__ ":" << __LINE__ << ")" << CLR_RESET << std::endl;
	(void)data;
}
void User::appendToWriteBuffer(const std::string &data) {
	std::cerr << CLR_RED << "Error: Method not found (" << __FILE_NAME__ ":" << __LINE__ << ")" << CLR_RESET << std::endl;
	(void)data;
}
std::string User::extractFullCommand() {
	std::cerr << CLR_RED << "Error: Method not found (" << __FILE_NAME__ ":" << __LINE__ << ")" << CLR_RESET << std::endl;
	return nullptr;
}

bool User::isReadyToSend() const {
	std::cerr << CLR_RED << "Error: Method not found (" << __FILE_NAME__ ":" << __LINE__ << ")" << CLR_RESET << std::endl;
	return (false);
}
