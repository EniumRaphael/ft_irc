/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:10:24 by sben-tay          #+#    #+#             */
/*   Updated: 2025/06/08 22:16:23 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cap.hpp"
#include "logs.hpp"

using namespace cmd;

cmd::Cap::Cap(User *user, Channel *channel, Server *server, const std::string &line)
	: ACommand(user, channel, server, line)
{
	_args = split(line);
	_command = "CAP";
}

void cmd::Cap::execute() {
	if (_args.size() >= 2 && _args[1] == "LS") {
		std::string reply = "CAP * LS :\r\n";
		_sender->appendToWriteBuffer(reply);
		DEBUG_MSG("Replied to CAP LS");
	}
}
