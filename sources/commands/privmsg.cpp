/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/19 02:28:16 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "privmsg.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

// exemple:
// PRIVMSG #samy :salut 

e_code PrivMsg::checkArgs() {
	if (_args.size() < 3) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}

	std::string target = _args.at(1);

	if (target[0] == '#') {
		target.erase(0, 1); // Enlève le '#'
		_cTarget = searchList(_server->getChannelsList(), target);
		if (_cTarget == NULL) {
			WARNING_MSG("Channel not found for PRIVMSG command");
			return ERR_NOSUCHCHANNEL;
		}
	} 
	else {
		_uTarget = searchList(_users, target);
		if (_uTarget == NULL || !_uTarget->isRegistered()) {
			WARNING_MSG("User not found or not registered");
			return ERR_NOSUCHNICK;
		}
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the PrivMsg command
 * @note To send a private message to a user / a channel
 */

void PrivMsg::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for PRIVMSG command (see warning message)");
		return;
	}

	std::string target = _args.at(1);
	std::string content = _args.at(2);
	std::string msg = ":" + _sender->getPrefix() + " PRIVMSG " + target + " :" + content + "\r\n";

	// Envoi vers un channel
	if (target[0] == '#') {
		target.erase(0, 1);
		if (_cTarget)
			_cTarget->sendAllClientInAChannel(msg, _sender); // Optionnel: évite d'envoyer au sender
	}
	// Envoi vers un user
	else {
		if (_uTarget)
			_uTarget->appendToWriteBuffer(msg);
	}
}
