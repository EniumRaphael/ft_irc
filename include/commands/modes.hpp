/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:17:31 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/17 16:37:07 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"
#include <string>
#include <utility>
#include <vector>

enum e_mode {
	ERROR_MODE = 0,
	CHAN_INVITE_ONLY,
	CHAN_SET_KEY,
	CHAN_SET_LIMIT,
	CHAN_SET_OP,
	CHAN_SET_TOPIC,
};

typedef struct s_mode {
	std::string arguments;
	bool add;
	bool remove;
}	t_mode;

class cmd::Mode : public ACommand {
	public:
		Mode(User *user, Channel *channel, Server *server,  std::string &line) : ACommand(user, channel, server, line) {}
		virtual void execute(void);
		virtual e_code checkArgs();
		void checkMode();
	private:
		std::vector<std::pair<e_mode, s_mode> > _mode;
};
