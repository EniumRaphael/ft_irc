/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:17:31 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/29 12:52:25 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

namespace cmd {
	class Pass : public ACommand {
		public:
			Pass(User *user, Channel *channel, Server *server,  std::string &line) : ACommand(user, channel, server, line) {}
			virtual void execute(void);
			virtual e_code checkArgs();
	};
}
