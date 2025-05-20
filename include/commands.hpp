/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:31:58 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/20 23:49:46 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "user.hpp"
#include "channel.hpp"

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

	class ICommand {
		private:
			std::string _command;
			std::vector<std::string> _args;
			User _user;
		public:
			virtual void execute() = 0;
			~ICommand();
			ICommand(User *user, Channel *channel, const std::string &line);
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
