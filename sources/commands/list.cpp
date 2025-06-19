/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/19 11:42:56 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include "channel.hpp"
#include "commands.hpp"
#include "logs.hpp"
#include <sstream>

using namespace cmd;

e_code List::checkArgs() {
	if (_args.size() < 1) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	if (this->_sender->isRegistered() == false) {
		WARNING_MSG("User is not registered for LIST command");
		INFO_MSG("You can only LIST registered users");
		return ERR_NOSUCHNICK;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the list command
 * @note To list the channel 
 */
void List::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for LIST command (see warning message)");
		return;
	}
	if (this->_args.size() > 1) {
		for (size_t i = 1; i < this->_args.size(); i++) {
		}
	} else {
		std::list<Channel *> &channelList = this->_server->getChannelsList();
		for (std::list<Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++) {
			DEBUG_MSG((*it)->getName());
			std::ostringstream msg322; msg322 << ":localhost 322 " << _sender->getNickname()
				<< " " << (*it)->getName() << " " <<
				(*it)->getUsers().size() <<
				" :" << (*it)->getTopic() << "\r\n";
			this->_sender->appendToWriteBuffer(msg322.str());
		}
	}
}
