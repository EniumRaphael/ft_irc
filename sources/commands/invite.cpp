/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/26 16:43:01 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "invite.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

bool Invite::checkArgs() {
	if (_args.size() < 2) {
		WARNING_MSG("Not enough arguments for INVITE command");
		return false;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for INVITE command");
		INFO_MSG("Channel names must start with a '#' character");
		return false;
	}
	_cTarget = searchList(_channels, _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for INVITE command");
		INFO_MSG("You can only invite users to channels you are in");
		return false;
	}
	if (searchList(_cTarget->getOperators(), _sender->getName()) != NULL) {
		WARNING_MSG("You are not an operator in the channel for INVITE command");
		return false;
	}
	uTarget = searchList(this->_users, _args.at(2));
	if (this->_uTarget == NULL) {
		WARNING_MSG("User not found");
		return false;
	}
	if (this->_uTarget->isRegistered() == false) {
		WARNING_MSG("User is not registered for INVITE command");
		INFO_MSG("You can only invite registered users");
		return false;
	}
	if (searchList(this->_cTarget->getUsers(), this->_uTarget->getName())) {
		WARNING_MSG("User is already in the channel for INVITE command");
		INFO_MSG("You cannot invite a user who is already in the channel");
		return false;
	}
	return true;
}

void Invite::execute() {
	if (checkArgs() == false) {
		ERROR_MSG("Invalid arguments for INVITE command (see warning message)");
		return;
	}
	// check how the com
}
