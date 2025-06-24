/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/24 14:35:17 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kick.hpp"
#include "commands.hpp"
#include "logs.hpp"
#include "bonus.hpp"

using namespace cmd;

e_code Kick::checkArgs() {
	if (_args.size() < 3) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for KICK command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	}
	_args.at(1).erase(0, 1); // On enlève le '#' pour chercher le nom réel
	_cTarget = searchList(this->_server->getChannelsList(), _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for KICK command");
		return ERR_NOSUCHCHANNEL;
	}
	if (searchList(_cTarget->getOperators(), _sender->getName()) == NULL) {
		WARNING_MSG("You are not an operator in the channel for KICK command");
		return ERR_CHANOPRIVSNEEDED;
	}

	if (BONUS && _args.at(2) == "bot" && _cTarget->getBotChannel()) {
		return _PARSING_OK;
	}

	_uTarget = searchList(this->_users, _args.at(2));
	if (_uTarget == NULL || !_uTarget->isRegistered()) {
		WARNING_MSG("User not found or not registered");
		return ERR_NOSUCHNICK;
	}
	if (searchList(this->_cTarget->getUsers(), _uTarget->getName()) == NULL) {
		WARNING_MSG("User is not in the channel for KICK command");
		return ERR_USERNOTINCHANNEL;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the KICK command
 * @note Operator removes a user from a channel
 */
void Kick::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for KICK command (see warning message)");
		return;
	}

	if (BONUS && _args.at(2) == "bot") {
		if (_cTarget->getBotChannel()) {
			std::string msgKickBot = ":bot!ircbot@localhost KICK #" + _cTarget->getName() + " " + "bot";
			if (_args.size() > 3)
				msgKickBot += " :" + _args.at(3);
			msgKickBot += "\r\n";
			std::cout << " msgKickBot: " << msgKickBot << std::endl;
			_cTarget->sendAllClientInAChannel(msgKickBot);
			_cTarget->setBotChannel(false);
		}
		return;
	}

	// std::string msgPart = ":" + _sender->getPrefix() + " PART #" + _cTarget->getName();
	
	std::string msgPart = ":" + this->_uTarget->getPrefix() + " PART #" + _cTarget->getName() + "\r\n";
	std::string msgKick = ":" + _sender->getPrefix() + " KICK #" + this->_cTarget->getName() + " " + _uTarget->getName();
	if (_args.size() > 3)
	{
		DEBUG_MSG("Je rajoute le message de kick avec un motif");
		msgKick += " :" + _args.at(3);
	}
	msgKick += "\r\n";

	std::cout << " msgKick: " << msgKick << "msgPart: " << msgPart << std::endl;
	_uTarget->appendToWriteBuffer(msgPart);
	_cTarget->sendAllClientInAChannel(msgKick);
	
	_cTarget->removeUser(this->_uTarget);
	_cTarget->removeOperator(this->_uTarget);

	if (_cTarget->getUsers().empty()) {
		std::list<Channel*>& allChannels = _server->getChannelsList();
		allChannels.remove(_cTarget);
		delete _cTarget;
		DEBUG_MSG("Channel supprimé car vide.");
	}
}
