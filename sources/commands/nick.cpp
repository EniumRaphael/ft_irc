/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/02 00:55:45 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nick.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

bool Nick::checkArgs() {
	if (this->_uTarget->isRegistered() == false) {
		WARNING_MSG("User is not registered for Nick command");
		INFO_MSG("You can only Nick registered users");
		return false;
	}
	if (_args.size() < 2) {
		WARNING_MSG("Not enough arguments for Nick command");
		return false;
	}
	_uTarget = searchList(this->_users, _args.at(1));
	if (this->_uTarget != NULL) {
		WARNING_MSG(_uTarget->getName() << " is already taken")
		return false;
	}
	return true;
}

/**
 * @brief Execute the Nick command
 * @note To change the nickname of the user
 */
void Nick::execute() {
	if (checkArgs() == false) {
		ERROR_MSG("Invalid arguments for Nick command (see warning message)");
		return;
	}
	// check how the com
}
