/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:17:31 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/02 00:34:16 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class cmd::Invite : public ACommand {
	public:
		Invite(User *user, Channel *channel, Server *server, const std::string &line) : ACommand(user, channel, server, line) {}
		virtual void execute(void);
		virtual bool checkArgs();
};
