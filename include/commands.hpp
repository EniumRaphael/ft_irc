/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:31:58 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/24 17:41:11 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "user.hpp"
#include "channel.hpp"
#include "server.hpp"
#include "logs.hpp"

namespace cmd
{
	/**
	 * @brief To send the line where a command is invoqued to execute
	 *
	 * @param user user who send the command
	 * @param channel channel where the command is sent
	 * @param line line send by the user
	 */
	void dispatch(User *user, Channel *channel, const std::string &line);
	std::vector<std::string> split(const std::string &line);
	template <typename T>
	T searchList(const std::list<T> &list, const std::string &name);

	class ACommand {
		protected:
			User* _sender;
			User* _uTarget;
			Channel *_channel;
			Channel *_cTarget;
			Server *_server;
			std::list<Channel *> _channels;
			std::list<User *> _users;
			std::string _command;
			std::vector<std::string> _args;
		public:
			virtual void execute() = 0;
			virtual bool checkArgs() = 0;
			~ACommand();
			ACommand(User *user, Channel *channel, Server *server, const std::string &line);
	};

	class Invite;
	class Join;
	class Kick;
	class List;
	class Mode;
	class Mode;
	class Nick;
	class Notice;
	class Part;
	class Pass;
	class Ping;
	class Pong;
	class PrivMsg;
	class Quit;
	class Topic;
	class Unknown;
	class User;
};

#include "./commands/commands.tpp"
