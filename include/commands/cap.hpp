/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:08:44 by sben-tay          #+#    #+#             */
/*   Updated: 2025/06/08 22:16:14 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class cmd::Cap : public ACommand {
	public:
		Cap(User *user, Channel *channel, Server *server, const std::string &line) : ACommand(user, channel, server, line) {}
		virtual void execute();
};