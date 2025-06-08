/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:10:24 by sben-tay          #+#    #+#             */
/*   Updated: 2025/06/08 22:45:35 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cap.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Cap::checkArgs() {
	return _PARSING_OK;
}

void cmd::Cap::execute() {
	DEBUG_MSG("coucou");
	if (this->checkArgs() != _PARSING_OK)
		return;
	DEBUG_MSG("coucou");
	if (_args.size() >= 2 && _args[1] == "LS") {
		std::string reply = "CAP * LS :\r\n";
		_sender->appendToWriteBuffer(reply);
		DEBUG_MSG("Replied to CAP LS");
	}
	DEBUG_MSG("coucou");
}
