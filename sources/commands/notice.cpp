/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/02 22:44:49 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notice.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

bool Notice::checkArgs() {
	if (_args.size() < 3) {
		WARNING_MSG("Not enough arguments for NOTICE command");
		return false;
	}
	if (_args.at(1).at(0) != '#') {
		_uTarget = searchList(this->_users, _args.at(2));
		if (this->_uTarget == NULL) {
			WARNING_MSG("User not found");
			return false;
		}
		if (this->_uTarget->isRegistered() == false) {
			WARNING_MSG("User is not registered for NOTICE command");
			INFO_MSG("You can only NOTICE registered users");
			return false;
		}
	} else {
		_cTarget = searchList(_channels, _args.at(1));
		if (_cTarget == NULL) {
			WARNING_MSG("Channel not found for NOTICE command");
			INFO_MSG("You can only NOTICE users to channels you are in");
			return false;
		} else
		_args.at(1).erase(0, 1);
	}
	return true;
}

/**
 * @brief Execute the Notice command
 * @note To send a private message to a user / a channel (like privmsg but without error)
 */
void Notice::execute() {
	if (checkArgs() == false) {
		ERROR_MSG("Invalid arguments for NOTICE command (see warning message)");
		return;
	}
	// check how the com
}
