/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/12 17:52:35 by sben-tay         ###   ########.fr       */
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

void Pass::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Pass command (see warning message)");
		DEBUG_MSG("skill issues");
		return;
	}
	DEBUG_MSG("mais pas trop skill issues");
	if (_args.at(1) != _server->getPassword()) {
		ERROR_MSG("The password is incorrect");
		return;
	}
	_sender->setHasPass(true);
	_sender->checkRegistration();
}
