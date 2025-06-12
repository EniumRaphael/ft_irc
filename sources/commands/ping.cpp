/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/12 13:24:55 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.hpp"
#include "commands.hpp"
#include "logs.hpp"
#include "pong.hpp"
#include <ctime>

using namespace cmd;

e_code Ping::checkArgs() {
	if (_args.size() < 3) {
		WARNING_MSG("Not enough arguments for PING command");
		return ERR_NEEDMOREPARAMS;
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the Ping
 * @note To send a private message to a user / a channel
 */

void Ping::execute() {
	clock_t start = clock() / CLOCKS_PER_SEC;
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for PRIVMSG command (see warning message)");
		return;
	}
	clock_t diff = Pong().answer(start);
	INFO_MSG(diff);
}
