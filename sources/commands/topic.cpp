/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/21 14:30:19 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "core.hpp"
#include "logs.hpp"
#include "topic.hpp"

using namespace cmd;

e_code Topic::checkArgs() {
	if (_args.size() < 3) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for KICK command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	this->_cTarget = searchList(this->_server->getChannelsList(), this->_args[1]);
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

	if (this->_args.size() == 1) {
		if (this->_cTarget->getTopic().empty()) {
			std::string msg331 = ":localhost 331 " + this->_sender->getNickname() + " #" + this->_cTarget->getName() + " :No topic is set\r\n";
			this->_sender->appendToWriteBuffer(msg331);
		} else {
			std::string msg332 = ":localhost 332 " + this->_sender->getNickname() + " #" + this->_cTarget->getName() + " :" + this->_cTarget->getTopic() + "\r\n";
			this->_sender->appendToWriteBuffer(msg332);
		}
	} else {
		std::string newTopic;
		for (size_t i = 2; i < this->_args.size(); ++i) {
			newTopic += this->_args[i];
			if (i != this->_args.size() - 1)
				newTopic += " ";
		}
		this->_cTarget->setTopic(newTopic);

		std::string topicMsg = ":" + this->_sender->getPrefix() + " TOPIC #" + this->_cTarget->getName() + " :" + newTopic + "\r\n";
		this->_cTarget->sendAllClientInAChannel(topicMsg);
	}
}
