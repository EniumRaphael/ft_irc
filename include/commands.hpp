/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:31:58 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/21 17:53:03 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "user.hpp"
#include "channel.hpp"
#include "server.hpp"
#include "core.hpp"
#include "logs.hpp"

namespace cmd
{
	void dispatch(User *user, Channel *channel, Server *server, std::string &line);
	std::vector<std::string> split(std::string &line, char sep);
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
			virtual e_code checkArgs() = 0;
			~ACommand();
			ACommand(User *user, Channel *channel, Server *server, std::string &line);
	};

	class Cap;
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
	class userCmd;
	class Whois;
	class Whowas;
};		

#include "./commands/commands.tpp"
