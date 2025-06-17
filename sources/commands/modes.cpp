/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/17 18:00:26 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modes.hpp"
#include "commands.hpp"
#include "core.hpp"
#include "logs.hpp"
#include <cerrno>
#include <cstdlib>
#include <utility>

using namespace cmd;

/**
 * @brief Check and chose the mode(s) for the commands
 */
void Mode::checkMode() {
	s_mode m;
	std::string flags = _args[2];
	size_t argIndex = 3;

	if (flags.empty() || (flags[0] != '+' && flags[0] != '-'))
	{
		m.add = false;
		m.remove = false;
		return;
	}
	bool add = (flags[0] == '+');
	for (size_t i = 1; i < flags.size(); ++i)
	{
		e_mode tmp = ERROR_MODE;
		s_mode m;
		m.add = add;
		m.remove = !add;
		m.arguments.clear();
		switch (flags[i])
		{
			case 'i':
				tmp = CHAN_INVITE_ONLY;
				break;
			case 't':
				tmp = CHAN_SET_TOPIC;
				break;
			case 'k':
				tmp = CHAN_SET_KEY;
				break;
			case 'l':
				tmp = CHAN_SET_LIMIT;
				break;
			case 'o':
				tmp = CHAN_SET_OP;
				break;
			default :
				break;
		}
		if ((this->_mode.back().first == CHAN_SET_KEY || this->_mode.back().first == CHAN_SET_LIMIT || this->_mode.back().first == CHAN_SET_OP) && argIndex < _args.size())
			m.arguments = _args[argIndex++];
		this->_mode.push_back(std::make_pair(tmp, m));
	}
}

/**
 * @brief Parsing of the mode command
 *
 * @return return the e_code if there is an error else return _PARSING_OK
 */
e_code Mode::checkArgs() {
	if (this->_args.size() < 2)
		return ERR_NEEDMOREPARAMS;
	if (this->_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for INVITE command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		this->_args.at(1).erase(0, 1);
	if (this->_cTarget == NULL) {
		WARNING_MSG("Channel not found for INVITE command");
		INFO_MSG("You can only invite users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	}
	if (this->_args.size() == 2) {
		return RPL_CHANNELMODEIS;
	}
	checkMode();
	if (this->_mode.empty())
		return ERR_UNKNOWNMODE;
	for (size_t i = 0; i < this->_mode.size(); ++i)
	{
		const e_mode &ret = this->_mode[i].first;
		if (ret == ERROR_MODE)
			return ERR_UNKNOWNMODE;
		if ((ret == CHAN_SET_KEY && this->_mode[i].second.add) || (ret == CHAN_SET_TOPIC && this->_mode[i].second.add) || (ret == CHAN_SET_LIMIT && this->_mode[i].second.add) || ret == CHAN_SET_OP)
			if (this->_mode[i].second.arguments.empty())
				return ERR_NEEDMOREPARAMS;
		if (searchList(this->_cTarget->getOperators(), this->_sender->getName()) != NULL) {
			WARNING_MSG("You are not an operator in the channel for INVITE command");
			return ERR_CHANOPRIVSNEEDED;
		}
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the mode command
 * @note To manipulate de moderation of a channel
 */
void Mode::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for INVITE command (see warning message)");
		return;
	}
	if (searchList(this->_cTarget->getOperators(), this->_sender->getName()) == NULL) {
		DEBUG_MSG("send is not an operator for MODE COMMAND");
	}
	for (size_t i = 0; i < this->_mode.size(); ++i) {
		size_t tmp;
		switch (this->_mode[i].first) {
			case CHAN_INVITE_ONLY:
				if (this->_mode[i].second.add) {
					if (this->_cTarget->getNeedInvite() == true) {
						DEBUG_MSG("Already as invite only");
					}
					this->_cTarget->setNeedInvite(true);
				} else if (this->_mode[i].second.remove) {
					if (this->_cTarget->getNeedInvite() == false) {
						DEBUG_MSG("Already as not invite only");
					}
					this->_cTarget->setNeedInvite(false);
				}
				break;
			case CHAN_SET_KEY:
				if (this->_mode[i].second.add)
					this->_cTarget->setPassword(this->_mode[i].second.arguments);
				else if (this->_mode[i].second.remove)
					this->_cTarget->setPassword("");
				break;
			case CHAN_SET_LIMIT:
				if (this->_mode[i].second.add) {
					errno = 0;
					tmp = strtol(this->_mode[i].second.arguments.c_str(), NULL, 10);
					if (tmp <= 0 || (this->_cTarget->getNeedInvite() && tmp >= this->_cTarget->getUsers().size()) || errno != ERANGE) {
						DEBUG_MSG("Overflow / negative number on mode +l abort");
						return;
					}
					this->_cTarget->setMaxUser(tmp);
				} else if (this->_mode[i].second.remove) {
					this->_cTarget->setMaxUser(0);
				}
				break;
			case CHAN_SET_OP:
				this->_uTarget = searchList(this->_cTarget->getUsers(), this->_mode[i].second.arguments);
				if (this->_uTarget == NULL)
					DEBUG_MSG("USER NOT FOUND");
				if (this->_mode[i].second.add) {
					this->_cTarget->getOperators().push_back(this->_uTarget);
				} else if (this->_mode[i].second.add) {
					if (searchList(this->_cTarget->getOperators(), this->_mode[i].second.arguments) == NULL) {
						DEBUG_MSG("NOT OPERATOR");
					} else {
						this->_cTarget->getOperators().remove(this->_uTarget);
					}
				}
				break;
			case CHAN_SET_TOPIC:
				if (this->_mode[i].second.add) {
					this->_cTarget->setTopic(this->_mode[i].second.arguments);
				} else if (this->_mode[i].second.remove) {
					this->_cTarget->setTopic("");
				}
				break;
			default:
				return;
		}
	}
}
