/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:11:56 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/03 16:46:58 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "logs.hpp"
#include "pass.hpp"
#include "ping.hpp"

/**
 * @brief To send the line where a command is invoqued to execute
 *
 * @param user user who send the command
 * @param channel channel where the command is sent
 * @param line line send by the user
 */
std::vector<std::string> cmd::split(const std::string &line) {
	std::vector<std::string> args;
	std::string arg;
	if (line.empty())
		return args;
	size_t pos = line.find(' ');
	while (pos != std::string::npos) {
		arg = line.substr(0, pos);
		if (!arg.empty()) {
			args.push_back(arg);
		}
		pos = line.find(' ');
	}
	if (!line.empty()) {
		args.push_back(line);
	}
	return args;
}

/**
 * @brief recieve the input of the user and execute the command asked
 *
 * @param user User how send the command
 * @param channel Channel where the command is sent
 * @param server Server where the command is sent
 * @param line input line from the user
 */
void cmd::dispatch(::User *user, Channel *channel, Server *server, const std::string &line) {
	DEBUG_MSG("in dispatch");
	std::vector<std::string> args = cmd::split(line);
	if (args.empty()) {
		ERROR_MSG("Empty line");
		return;
	}
	std::string command_name = args[0];
	if (command_name.empty()) {
		WARNING_MSG("No command found in line: " << line);
		return;
	}
	if (command_name[0] == '/') {
		command_name.erase(0, 1);
	} else {
		WARNING_MSG("Command does not start with '/': " << command_name);
		return;
	}
	switch (command_name[0]) {
		case 'i':
			// if (command_name == "invite") {
			// 	Invite(user, channel, server, line).execute();
			// }
			break;
		case 'j':
			// if (command_name == "join") {
			// 	Join(user, channel, server, line).execute();
			// }
			break;
		case 'k':
			// if (command_name == "kick") {
			// 	Kick(user, channel, server, line).execute();
			// }
			break;
		case 'l':
			// if (command_name == "list") {
			// 	List(user, channel, server, line).execute();
			// }
			break;
		case 'm':
			// if (command_name == "mode") {
			// 	Mode(user, channel, server, line).execute();
			// }
			break;
		case 'n':
			// if (command_name == "nick") {
			// 	Nick(user, channel, server, line).execute();
			// } else if (command_name == "notice") {
			// 	Notice(user, channel, server, line).execute();
			// }
			break;
		case 'p':
			if (command_name == "pass") {
				Pass(user, channel, server, line).execute();
			}
			if (command_name == "ping") {
				Ping(user, channel, server, line).execute();
			}
			// if (command_name == "part") {
			// 	Part(user, channel, server, line).execute();
			// }
			break;
		default:
			WARNING_MSG("Unknown command: " << command_name);
	}
	(void)user;
	(void)server;
	(void)channel;
	(void)line;
}

cmd::ACommand::ACommand(::User *user, ::Channel *channel, ::Server *server, const std::string &line) : _sender(user), _channel(channel), _server(server) {
	DEBUG_MSG("ACommand constructor called");
	_args = split(line);
	_command = _args.at(0);
	_channels = server->getChannelsList();
	_users = server->getUsersList();
	_uTarget = NULL;
	_cTarget = NULL;
}

cmd::ACommand::~ACommand() {
	DEBUG_MSG("ACommand destructor called");
}
