/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:16:10 by sben-tay          #+#    #+#             */
/*   Updated: 2025/06/17 23:17:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "userCmd.hpp"
#include "logs.hpp"

using namespace cmd;

e_code cmd::userCmd::checkArgs() {
	if (_args.size() < 5) {
		WARNING_MSG("USER: Not enough parameters");
		return ERR_NEEDMOREPARAMS;
	}
	return _PARSING_OK;
}

void cmd::userCmd::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("USER: bad args");
		return;
	}

	DEBUG_MSG("Setting username to " << _args[1]);
	_sender->setUsername(_args[1]);
	_sender->setHasUser(true);
	_sender->setRealname(_args[4]);
	_sender->checkRegistration();
}

