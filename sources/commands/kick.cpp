/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/21 19:19:30 by sben-tay         ###   ########.fr       */
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
	} else
		_args.at(1).erase(0, 1);
	_cTarget = searchList(this->_server->getChannelsList(), _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for KICK command");
		INFO_MSG("You can only KICK users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	if (searchList(_cTarget->getOperators(), _sender->getName()) == NULL) {
		WARNING_MSG("You are not an operator in the channel for KICK command");
		return ERR_CHANOPRIVSNEEDED;
	}
	_uTarget = searchList(this->_users, _args.at(2));

	if (BONUS && _args.at(2) == "bot" && _cTarget->getBotChannel() == true) {
		return _PARSING_OK;
	}
	else if (this->_uTarget == NULL) {
		WARNING_MSG("User not found");
		return ERR_NOSUCHNICK;
	}
	if (this->_uTarget->isRegistered() == false) {
		WARNING_MSG("User is not registered for KICK command");
		INFO_MSG("You can only KICK registered users");
		return ERR_NOSUCHNICK;
	}
	if (searchList(this->_cTarget->getUsers(), this->_uTarget->getName()) == NULL) {
		WARNING_MSG("User is already in the channel for KICK command");
		INFO_MSG("You cannot KICK a user who is already in the channel");
		return ERR_USERONCHANNEL;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the kick command
 * @note To kick a user from a channel
 */
void Kick::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for INVITE command (see warning message)");
		return;
	}
	std::cout << "MODE BONUS ?" << BONUS << std::endl;
	if (BONUS && _args.at(2) == "bot") {
		if (_cTarget->getBotChannel() == true) {
			std::cout << "Bot is already in the channel, kicking it" << std::endl;
			std::string msgKickBot = ":bot!ircbot@localhost KICK #" + _cTarget->getName() + " bot :Bot kicked from channel\r\n";
			this->_sender->appendToWriteBuffer(msgKickBot);
			_cTarget->setBotChannel(false);
		}
		std::cout << "peace" << std::endl;
		return;
	}
	std::string msgPart = ":" + this->_uTarget->getPrefix() + " PART #" + _cTarget->getName() + "\r\n";
	std::string msgKick = ":" + this->_uTarget->getPrefix() + " KICK #" + this->_cTarget->getName() + " " + this->_uTarget->getName() + " :kicked from channel\r\n";
	if (_args.size() > 4)
		msgKick += " :" + _args.at(4);
	msgKick += "\r\n";

	this->_uTarget->appendToWriteBuffer(msgKick + msgPart);
	_cTarget->removeUser(this->_uTarget);
	_cTarget->removeOperator(this->_uTarget);

	if (_cTarget->getUsers().empty()) {
		std::list<Channel*>& allChannels = _server->getChannelsList();
		allChannels.remove(_cTarget);
		delete _cTarget;
		DEBUG_MSG("Channel supprimé car vide.");
	}
}
