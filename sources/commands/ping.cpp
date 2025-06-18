/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/18 12:53:01 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.hpp"
#include "commands.hpp"
#include "logs.hpp"
#include "pong.hpp"
#include <ctime>

using namespace cmd;

e_code Ping::checkArgs() {
	if (_args.size() < 2) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Ping
 * @note To send a private message to a user / a channel
 */

void Ping::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for PRIVMSG command (see warning message)");
		return;
	}
	std::string msgpong = "PONG " + _args[1] + "\r\n";
	_sender->appendToWriteBuffer(msgpong);
	DEBUG_MSG(_sender->getWriteBuffer());
}
