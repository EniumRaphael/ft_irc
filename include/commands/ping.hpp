/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:48:36 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/02 22:48:48 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class cmd::Ping : public ACommand {
	public:
		Ping(User *user, Channel *channel, Server *server, const std::string &line) : ACommand(user, channel, server, line) {}
		virtual void execute(void);
		virtual bool checkArgs();
};
