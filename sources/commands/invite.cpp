/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/24 17:58:36 by rparodi          ###   ########.fr       */
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
	if (_cTarget == nullptr) {
		WARNING_MSG("Channel not found for INVITE command");
		INFO_MSG("You can only invite users to channels you are in");
		return false;
	}
	if (searchList(_cTarget->getOperators(), _sender->getName()) != nullptr) {
		WARNING_MSG("You are not an operator in the channel for INVITE command");
		return false;
	}
	return (true);
}
