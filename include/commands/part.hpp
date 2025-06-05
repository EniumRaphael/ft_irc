/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:17:31 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/04 23:49:09 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class cmd::Part : public ACommand {
	public:
		Part(User *user, Channel *channel, Server *server, const std::string &line) : ACommand(user, channel, server, line) {}
		virtual void execute(void);
		virtual e_code checkArgs();
};
