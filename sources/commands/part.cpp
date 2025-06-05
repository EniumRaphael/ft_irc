/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/05 22:50:21 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "part.hpp"
#include "commands.hpp"
#include "core.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Part::checkArgs() {
	if (_args.size() < 2) {
		WARNING_MSG("Not enough arguments for PART command");
		return ERR_NEEDMOREPARAMS;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for PART command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	_cTarget = searchList(_channels, _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for PART command");
		INFO_MSG("You can only Part users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	if (searchList(this->_cTarget->getUsers(), this->_uTarget->getName())) {
		WARNING_MSG("User is not in the channel he wants to leave");
		INFO_MSG("You cannot leave a channel where ur not a member");
		return ERR_USERNOTINCHANNEL;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Part command
 * @note To leave a channel givent in parameter
 */
void Part::execute() {
	if (checkArgs() == _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Part command (see warning message)");
		return;
	}
	// check how the com
}
