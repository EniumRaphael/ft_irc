/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whowas.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:02:03 by sben-tay          #+#    #+#             */
/*   Updated: 2025/06/17 17:05:21 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whowas.hpp"
#include "logs.hpp"

e_code cmd::Whowas::checkArgs() {
	if (_args.size() < 2 || _args[1].empty()) {
		WARNING_MSG("Whowas: Not enough arguments");
		return ERR_NONICKNAMEGIVEN;
	}
	return _PARSING_OK;
}

void cmd::Whowas::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Whowas command");
		return;
	}

	User* requestingUser = _sender;
	std::string nickname = _args[1];

	std::string msg406 = ":localhost 406 " + requestingUser->getNickname() + " " +
	                     nickname + " :There was no such nickname\r\n";
	std::string msg369 = ":localhost 369 " + requestingUser->getNickname() + " " +
	                     nickname + " :End of WHOWAS\r\n";

	/*
		plus tard on pourrait implémenter une liste de whowas sur les user deconnectés
		pour que la fonction soit complete.
	*/
	
	requestingUser->appendToWriteBuffer(msg406);
	requestingUser->appendToWriteBuffer(msg369);
}