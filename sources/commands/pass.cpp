/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/16 17:33:20 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pass.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Pass::checkArgs() {
	if (_args.size() != 2) {
		WARNING_MSG("Not correct for Pass command");
		return ERR_NEEDMOREPARAMS;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Pass command
 * @note To connect a user with the password
 */

void cmd::Pass::execute() {
	if (_args.size() < 2) {
		_sender->appendToWriteBuffer(":localhost 461 PASS :Not enough parameters\r\n");
		return;
	}
	_sender->setHasPass(true);
	_sender->setPassReceived(true);
	if (_args[1] == _server->getPassword())
	{
		DEBUG_MSG("PASSISVALID");
		_sender->setPassIsValid(true);
	}
	else{
		DEBUG_MSG("PASSISINVALID");
		_sender->setPassIsValid(false);
	}

	_sender->checkRegistration();
}
