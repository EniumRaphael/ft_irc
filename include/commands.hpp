/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:31:58 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/20 23:41:28 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "user.hpp"

namespace cmd
{
	void dispatch(User user, const std::string &line);
	std::vector<std::string> split(const std::string &line);

	class ACommand {
		private:
			std::string _command;
			std::vector<std::string> _args;
			User _user;
		public:
			virtual bool execute() = 0;
			~ACommand();
			ACommand(User user, const std::string &line);
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
