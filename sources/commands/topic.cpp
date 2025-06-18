/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/18 12:51:40 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "core.hpp"
#include "logs.hpp"
#include "topic.hpp"

using namespace cmd;

e_code Topic::checkArgs() {
	if (_args.size() < 2) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	this->_cTarget = searchList(this->_channels, this->_args[1]);
	if (this->_cTarget == NULL)
		return ERR_NOSUCHCHANNEL;
	if (this->_cTarget->getProtectTopic()) {
		if (searchList(this->_cTarget->getOperators(), this->_sender->getName()) == NULL)
			return ERR_CHANOPRIVSNEEDED;
	} else {
		if (searchList(this->_cTarget->getUsers(), this->_sender->getName()) == NULL)
			return ERR_NOTONCHANNEL;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Topic
 * @note To change the topic of the channel
 */

void Topic::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for TOPIC command (see warning message)");
		return;
	}
	if (this->_cTarget->getTopic().empty()) {
		std::string msg331 = ":localhost 331 " + this->_sender->getNickname() + " " + this->_cTarget->getName() + " :No topic is set" + "\r\n";
		this->_sender->appendToWriteBuffer(msg331);
	} else {
		std::string msg332 = ":localhost 332 " + this->_sender->getNickname() + " " + this->_cTarget->getName() + " :" + _cTarget->getTopic() + "\r\n";
		this->_sender->appendToWriteBuffer(msg332);
	}
}
