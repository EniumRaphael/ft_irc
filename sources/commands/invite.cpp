/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/19 13:53:17 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "invite.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Invite::checkArgs() {
	if (_args.size() < 3) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for INVITE command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	_cTarget = searchList(_server->getChannelsList(), _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for INVITE command");
		INFO_MSG("You can only invite users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	}
	if (searchList(_cTarget->getOperators(), _sender->getName()) == NULL) {
		WARNING_MSG("You are not an operator in the channel for INVITE command");
		return ERR_NOPRIVILEGES;
	}
	_uTarget = searchList(this->_users, _args.at(2));
	if (this->_uTarget == NULL) {
		WARNING_MSG("User not found");
		return ERR_NOSUCHNICK;
	}
	if (this->_uTarget->isRegistered() == false) {
		WARNING_MSG("User is not registered for INVITE command");
		INFO_MSG("You can only invite registered users");
		return ERR_NOSUCHNICK;
	}
	if (searchList(this->_cTarget->getUsers(), this->_uTarget->getName())) {
		WARNING_MSG("User is already in the channel for INVITE command");
		INFO_MSG("You cannot invite a user who is already in the channel");
		return ERR_USERONCHANNEL;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the invite command
 * @note To invite a peapol to join a channel (from an operator)
 */

void Invite::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for INVITE command (see warning message)");
		return;
	}

	_cTarget->addInvited(_uTarget);

	std::string msgToInvited = ":" + _sender->getPrefix() + " INVITE " + _uTarget->getNickname() + " #" + _cTarget->getName() + "\r\n";
	_uTarget->appendToWriteBuffer(msgToInvited);

	std::string msg341 = ":localhost 341 " + _sender->getNickname() + " " + _uTarget->getNickname() + " #" + _cTarget->getName() + "\r\n";
	_sender->appendToWriteBuffer(msg341);
}
