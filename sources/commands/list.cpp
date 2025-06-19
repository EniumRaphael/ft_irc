/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/19 13:50:09 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include "channel.hpp"
#include "commands.hpp"
#include "logs.hpp"
#include <sstream>

using namespace cmd;

e_code List::checkArgs() {
	if (_args.size() < 1) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}
	if (this->_sender->isRegistered() == false) {
		WARNING_MSG("User is not registered for LIST command");
		INFO_MSG("You can only LIST registered users");
		return ERR_NOSUCHNICK;
	}
	if (this->_args.size() == 2) {
		std::string tmp_line = this->_args.back();
		this->_args.pop_back();
		std::vector<std::string> tmp = split(tmp_line, ',');
		for (size_t i = 0; i < tmp.size(); i++) {
			this->_args.push_back(tmp.back());
			tmp.pop_back();
		}
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the list command
 * @note To list the channel 
 */
void List::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for LIST command (see warning message)");
		return;
	}
	std::string msg321 = ":localhost 321 " + _sender->getNickname() + " Channel :Users  Name\r\n";
	this->_sender->appendToWriteBuffer(msg321);
	if (this->_args.size() > 1) {
		std::vector<std::string> vec_tmp;
		bool to_print = true;
		for (size_t i = 1; i < this->_args.size(); ++i) {
			DEBUG_MSG("[" << i << "] " << this->_args[i]);
			if (this->_args[i][0] == '#')
				this->_args[i].erase(0, 1);
			else {
				WARNING_MSG("Thanks to check if all the Channel have an '#' at the start of the name !");
				to_print = false;
				break;
			}
			this->_cTarget = searchList(this->_server->getChannelsList(), this->_args[i]);
			if (this->_cTarget == NULL) {
				WARNING_MSG("Channel not found, aborting the command !");
				to_print = false;
				break;
			} else {
				std::ostringstream tmp;
				tmp << ":localhost 322 " << _sender->getNickname()
					<< " " << this->_cTarget->getName() << " " <<
					this->_cTarget->getUsers().size() <<
					" :" << this->_cTarget->getTopic() << "\r\n";
				vec_tmp.push_back(tmp.str());
			}
		}
		if (to_print) {
			for (size_t j = 0; j < vec_tmp.size(); j++) {
				DEBUG_MSG(vec_tmp[j]);
				this->_sender->appendToWriteBuffer(vec_tmp[j]);
			}
		}
	} else {
		for (std::list<Channel *>::iterator it = this->_server->getChannelsList().begin(); it != this->_server->getChannelsList().end(); it++) {
			std::ostringstream msg322; msg322 << ":localhost 322 " << _sender->getNickname()
				<< " " << (*it)->getName() << " " <<
				(*it)->getUsers().size() <<
				" :" << (*it)->getTopic() << "\r\n";
			this->_sender->appendToWriteBuffer(msg322.str());
		}
	}
	std::string msg323 = ":localhost 323 " + _sender->getNickname() + " :End of /LIST\r\n";
	this->_sender->appendToWriteBuffer(msg323);
}
