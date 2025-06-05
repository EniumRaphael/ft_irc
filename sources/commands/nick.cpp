/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/05 22:48:17 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nick.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Nick::checkArgs() {
	if (this->_uTarget->isRegistered() == false) {
		WARNING_MSG("User is not registered for Nick command");
		INFO_MSG("You can only Nick registered users");
		return ERR_NOSUCHNICK;
	}
	if (_args.size() < 2) {
		WARNING_MSG("Not enough arguments for Nick command");
		return ERR_NEEDMOREPARAMS;
	}
	_uTarget = searchList(this->_users, _args.at(1));
	if (this->_uTarget != NULL) {
		WARNING_MSG(_uTarget->getName() << " is already taken")
		return ERR_NICKNAMEINUSE;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Nick command
 * @note To change the nickname of the user
 */
void Nick::execute() {
	if (checkArgs() == _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Nick command (see warning message)");
		return;
	}
	// check how the com
}
