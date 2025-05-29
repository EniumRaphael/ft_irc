/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/29 12:41:39 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pass.hpp"
#include "commands.hpp"
#include "logs.hpp"

using namespace cmd;

bool Pass::checkArgs() {
	if (_args.size() != 2) {
		WARNING_MSG("Not correct for Pass command");
		return false;
	}
	if (_sender->isRegistered()) {
		WARNING_MSG(_sender->getName() << " is already is already log in the server !");
		return false;
	}
	return true;
}

/**
 * @brief Execute the Pass command
 * @note To Pass a users to join a channel (from an operator)
 */
void Pass::execute() {
	if (checkArgs() == false) {
		ERROR_MSG("Invalid arguments for Pass command (see warning message)");
		return;
	}
	if (_args.at(1) != _server->getPassword()) {
		ERROR_MSG("The password is incorrect");
		return;
	}
	_sender->setRegistered();
}
