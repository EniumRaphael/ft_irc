/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:10:24 by sben-tay          #+#    #+#             */
/*   Updated: 2025/06/20 19:18:52 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cap.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Cap::checkArgs() {
	if (_args.size() < 2) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	return (_PARSING_OK);
}

void cmd::Cap::execute() {
	if (this->checkArgs() != _PARSING_OK)
		return;
	if (_args.size() >= 2 && _args[1] == "ls") {
		std::string reply = "CAP * LS :\r\n";
		_sender->appendToWriteBuffer(reply);
		DEBUG_MSG("Replied to CAP LS");
	}
}
