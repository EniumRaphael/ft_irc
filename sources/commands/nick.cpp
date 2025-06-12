/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/12 17:52:12 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nick.hpp"
#include "logs.hpp"

using namespace cmd;

e_code cmd::Nick::checkArgs() {
	if (_args.size() < 2 || _args[1].empty()) {
		WARNING_MSG("Nick: Not enough arguments");
		return ERR_NONICKNAMEGIVEN;
	}
	User* existing = searchList<User*>(_users, _args[1]); // à adapter si besoin
	if (existing != NULL) {
		
		WARNING_MSG("Nick already in use: " << _args[1]);
		return ERR_NICKNAMEINUSE;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Nick command
 * @note To change the nickname of the user
 */
void cmd::Nick::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Nick command (see warning message)");
		return;
	}
	DEBUG_MSG("Setting nickname to " << _args[1]);
	_sender->setNickname(_args[1]);
	_sender->setHasNick(true);
	_sender->checkRegistration();
}
