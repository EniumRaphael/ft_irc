 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:11:56 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/10 16:25:57 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include <cctype>
#include "join.hpp"
#include "privmsg.hpp"
#include "nick.hpp"
#include "invite.hpp"
#include "list.hpp"
#include "cap.hpp"
#include "modes.hpp"
#include "ping.hpp"
#include "notice.hpp"
#include "kick.hpp"
#include "userCmd.hpp"
#include "pass.hpp"
#include "part.hpp"
#include <iterator>

/**
 * @brief To send the line where a command is invoqued to execute
 *
 * @param user user who send the command
 * @param channel channel where the command is sent
 * @param line line send by the user
 */

std::vector<std::string> cmd::split(std::string &line) {
	std::vector<std::string> args;
	size_t start = 0;
	size_t end;

	while ((end = line.find(' ', start)) != std::string::npos) {
		std::string arg = line.substr(start, end - start);
		if (!arg.empty()) {
			for (size_t i = 0; i < arg.length(); ++i)
				arg[i] = std::tolower(arg[i]);
			args.push_back(arg);
		}
		start = end + 1;
	}
	if (start < line.length()) {
		std::string arg = line.substr(start);
		for (size_t i = 0; i < arg.length(); ++i)
			arg[i] = std::tolower(arg[i]);
		args.push_back(arg);
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
void cmd::dispatch(::User *user, Channel *channel, Server *server, std::string &line) {
	std::vector<std::string> args = cmd::split(line);
	if (args.empty()) {
		DEBUG_MSG("Empty line");
		return;
	}
	std::string command_name = args[0];
	if (command_name.empty()) {
		WARNING_MSG("No command found in line: " << line);
		return;
	}
	DEBUG_MSG("Command Name = [" << command_name << "]");
	switch (command_name[0]) {
		case 'c':
			if (command_name == "cap") {
				Cap(user, channel, server, line).execute();
			}
			break;
		case 'i':
			if (command_name == "invite") {
				Invite(user, channel, server, line).execute();
			}
			break;
		case 'j':
			if (command_name == "join") {
				Join(user, channel, server, line).execute();
			}
			break;
		case 'k':
			if (command_name == "kick") {
				Kick(user, channel, server, line).execute();
			}
			break;
		case 'l':
			if (command_name == "list") {
				List(user, channel, server, line).execute();
			}
			break;
		case 'm':
			if (command_name == "mode") {
				Mode(user, channel, server, line).execute();
			}
			break;
		case 'n':
			if (command_name == "nick") {
				Nick(user, channel, server, line).execute();
			} else if (command_name == "notice") {
				Notice(user, channel, server, line).execute();
			}
			break;
		case 'p':
			if (command_name == "pass") {
				Pass(user, channel, server, line).execute();
			}
			if (command_name == "privmsg") {
				PrivMsg(user, channel, server, line).execute();
			}
			if (command_name == "ping") {
				Ping(user, channel, server, line).execute();
			}
			if (command_name == "part") {
				Part(user, channel, server, line).execute();
			}
			break;
		case 'u':
			if (command_name == "user") {
				userCmd(user, channel, server, line).execute();
			}
			break;
		default:
			WARNING_MSG("Unknown command: " << command_name);
	}
	(void)user;
	(void)server;
	(void)channel;
	(void)line;
}

cmd::ACommand::ACommand(::User *user, ::Channel *channel, ::Server *server, std::string &line) : _sender(user), _channel(channel), _server(server) {
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
