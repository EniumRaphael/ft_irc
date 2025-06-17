/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:01:46 by sben-tay          #+#    #+#             */
/*   Updated: 2025/06/17 16:55:08 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whois.hpp"
#include "logs.hpp"

using namespace cmd;

e_code Whois::checkArgs() {
	if (_args.size() < 2 || _args[1].empty()) {
		WARNING_MSG("Whois: Not enough arguments");
		return ERR_NONICKNAMEGIVEN;
	}
	return _PARSING_OK;
}

void Whois::execute()
{
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Whois command (see warning message)");
		return;
	}

	User* requestingUser = _sender;
	User* targetUser = searchList<User*>(_users, _args[1]);
	if (targetUser == NULL) {
		std::string errMsg = ":localhost 401 " + requestingUser->getNickname() + " " + _args[1] + " :No such nick/channel\r\n";
		requestingUser->appendToWriteBuffer(errMsg);
		return;
	}

	std::string msg311 = ":localhost 311 " + requestingUser->getNickname() + " " +
	                     targetUser->getNickname() + " " +
	                     targetUser->getUsername() + " " +
	                     targetUser->getHostname() + " * :" +
	                     targetUser->getRealname() + "\r\n";

	std::string msg318 = ":localhost 318 " + requestingUser->getNickname() + " " +
	                     targetUser->getNickname() + " :End of /WHOIS list\r\n";

	requestingUser->appendToWriteBuffer(msg311);
	requestingUser->appendToWriteBuffer(msg318);
}
