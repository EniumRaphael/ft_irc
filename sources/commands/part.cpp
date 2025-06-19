/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/19 01:13:28 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "part.hpp"
#include "commands.hpp"
#include "core.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Part::checkArgs() {
	if (_args.size() < 2) {
		DEBUG_MSG("Not enough arguments for Part command");
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	DEBUG_MSG("Arguments size is valid for Part command");
	if (_args.at(1).at(0) != '#') {
		DEBUG_MSG("Invalid channel name for Part command: " << _args.at(1));
		WARNING_MSG("Invalid channel name for PART command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else {
		_args.at(1).erase(0, 1);
	}
	_cTarget = searchList(_server->getChannelsList(), _args.at(1));
	if (_cTarget == NULL) {
		DEBUG_MSG("Channel not found for Part command: " << _args.at(1));
		WARNING_MSG("Channel not found for PART command");
		INFO_MSG("You can only Part users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	}
	if (_cTarget->isUserInChannel(_sender) == false) {
		DEBUG_MSG("sender is : " << _sender->getName());
		WARNING_MSG("User is not in the channel he wants to leave");
		INFO_MSG("You cannot leave a channel where ur not a member");
		return ERR_USERNOTINCHANNEL;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Part command
 * @note To leave a channel givent in parameter
 */

void Part::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Part command (see warning message)");
		return;
	}
	DEBUG_MSG("EXECUTING PART COMMAND");

	std::string msgPart = ":" + _sender->getPrefix() + " PART #" + _cTarget->getName();
	if (_args.size() > 2)
		msgPart += " :" + _args.at(2);
	msgPart += "\r\n";

	_cTarget->sendAllClientInAChannel(msgPart);
	_cTarget->removeUser(_sender);
	_cTarget->removeOperator(_sender);
	// remove invited list

	if (_cTarget->getUsers().empty()) {
		std::list<Channel*>& allChannels = _server->getChannelsList();
		allChannels.remove(_cTarget);
		delete _cTarget;
		DEBUG_MSG("Channel supprimé car vide.");
	}
}
