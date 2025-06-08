/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:17:31 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/02 00:33:23 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class cmd::Join : public ACommand {
	public:
		Join(User *user, Channel *channel, Server *server,  std::string &line) : ACommand(user, channel, server, line) {}
		virtual void execute(void);
		virtual e_code checkArgs();
};
