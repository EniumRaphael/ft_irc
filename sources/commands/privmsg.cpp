/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/12 13:25:02 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "privmsg.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

e_code PrivMsg::checkArgs() {
	if (_args.size() < 3) {
		WARNING_MSG("Not enough arguments for PRIVMSG command");
		return ERR_NEEDMOREPARAMS;
	}
	if (_args.at(1).at(0) != '#') {
		_uTarget = searchList(this->_users, _args.at(2));
		if (this->_uTarget == NULL) {
			WARNING_MSG("User not found");
			return ERR_NOSUCHNICK;
		}
		if (this->_uTarget->isRegistered() == false) {
			WARNING_MSG("User is not registered for PRIVMSG command");
			INFO_MSG("You can only privmsg registered users");
			return ERR_NOSUCHNICK;
		}
	} else {
		_cTarget = searchList(_channels, _args.at(1));
		if (_cTarget == NULL) {
			WARNING_MSG("Channel not found for PRIVMSG command");
			INFO_MSG("You can only privmsg users to channels you are in");
			return ERR_NOSUCHCHANNEL;
		} else
		_args.at(1).erase(0, 1);
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the PrivMsg command
 * @note To send a private message to a user / a channel
 */
void PrivMsg::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for PRIVMSG command (see warning message)");
		return;
	}
	// check how the com
}
