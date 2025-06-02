/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/02 22:42:17 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "join.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

bool Join::checkArgs() {
	if (_args.size() < 2) {
		WARNING_MSG("Not enough arguments for Join command");
		return false;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for Join command");
		INFO_MSG("Channel names must start with a '#' character");
		return false;
	} else
		_args.at(1).erase(0, 1);
	_cTarget = searchList(_channels, _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for Join command");
		INFO_MSG("You can only Join users to channels you are in");
		return false;
	}
	if (searchList(_cTarget->getOperators(), _sender->getName()) != NULL) {
		WARNING_MSG("You are not an operator in the channel for Join command");
		return false;
	}
	if (searchList(_cTarget->getInvited(), _sender->getName()) != NULL) {
		WARNING_MSG("This channel is private and ur not invited");
		return false;
	}
	return true;
}

/**
 * @brief Execute the join command
 * @note To join a new channel
 */
void Join::execute() {
	if (checkArgs() == false) {
		ERROR_MSG("Invalid arguments for Join command (see warning message)");
		return;
	}
}
