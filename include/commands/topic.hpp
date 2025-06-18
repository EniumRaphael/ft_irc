/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:48:36 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/17 22:10:31 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class cmd::Topic : public ACommand {
	public:
		Topic(User *user, Channel *channel, Server *server,  std::string &line) : ACommand(user, channel, server, line) {}
		virtual void execute(void);
		virtual e_code checkArgs();
};
