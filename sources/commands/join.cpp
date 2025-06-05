/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/05 22:34:07 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "join.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Join::checkArgs() {
	if (_args.size() < 2) {
		WARNING_MSG("Not enough arguments for Join command");
		return ERR_NEEDMOREPARAMS;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for Join command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	_cTarget = searchList(_channels, _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for Join command");
		INFO_MSG("You can only Join users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	}
	if (searchList(_cTarget->getOperators(), _sender->getName()) != NULL) {
		WARNING_MSG("You are not an operator in the channel for Join command");
		return ERR_NOPRIVILEGES;
	}
	if (searchList(_cTarget->getInvited(), _sender->getName()) != NULL) {
		WARNING_MSG("This channel is private and ur not invited");
		return ERR_INVITEONLYCHAN;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the join command
 * @note To join a new channel
 */
void Join::execute() {
	if (checkArgs() == _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Join command (see warning message)");
		return;
	}
}
