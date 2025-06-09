/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/09 15:33:52 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

e_code List::checkArgs() {
	if (_args.size() < 3) {
		WARNING_MSG("Not enough arguments for LIST command");
		return ERR_NEEDMOREPARAMS;
	}
	if (this->_sender->isRegistered() == false) {
		WARNING_MSG("User is not registered for LIST command");
		INFO_MSG("You can only LIST registered users");
		return ERR_NOSUCHNICK;
	}
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for LIST command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	_cTarget = searchList(_channels, _args.at(1));
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for LIST command");
		INFO_MSG("You can only LIST users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	return _PARSING_OK;
}

/**
 * @brief Execute the list command
 * @note To list the channel 
 */
void List::execute() {
	if (checkArgs() == _PARSING_OK) {
		ERROR_MSG("Invalid arguments for LIST command (see warning message)");
		return;
	}
	// check how the com
}
