/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/09 14:37:11 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kick.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Kick::checkArgs() {
	if (_args.size() < 3) {
		WARNING_MSG("Not enough arguments for KICK command");
		return ERR_NEEDMOREPARAMS;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for KICK command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	_cTarget = searchList(_channels, _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for KICK command");
		INFO_MSG("You can only KICK users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	if (searchList(_cTarget->getOperators(), _sender->getName()) != NULL) {
		WARNING_MSG("You are not an operator in the channel for KICK command");
		return ERR_CHANOPRIVSNEEDED;
	}
	_uTarget = searchList(this->_users, _args.at(2));
	if (this->_uTarget == NULL) {
		WARNING_MSG("User not found");
		return ERR_NOSUCHNICK;
	}
	if (this->_uTarget->isRegistered() == false) {
		WARNING_MSG("User is not registered for KICK command");
		INFO_MSG("You can only KICK registered users");
		return ERR_NOSUCHNICK;
	}
	if (searchList(this->_cTarget->getUsers(), this->_uTarget->getName())) {
		WARNING_MSG("User is already in the channel for KICK command");
		INFO_MSG("You cannot KICK a user who is already in the channel");
		return ERR_USERONCHANNEL;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the kick command
 * @note To kick a user from a channel
 */
void Kick::execute() {
	if (checkArgs() == _PARSING_OK) {
		ERROR_MSG("Invalid arguments for INVITE command (see warning message)");
		return;
	}
	// check how the com
}
