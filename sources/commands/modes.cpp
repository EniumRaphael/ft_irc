/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/10 16:08:09 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modes.hpp"
#include "commands.hpp"
#include "core.hpp"
#include "logs.hpp"
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
		m.mode = ERROR_MODE;
		return;
	}
	bool add = (flags[0] == '+');
	for (size_t i = 1; i < flags.size(); ++i)
	{
		s_mode m;
		m.mode = ERROR_MODE;
		m.add = add;
		m.remove = !add;
		m.arguments.clear();
		switch (flags[i])
		{
			case 'i':
				m.mode = CHAN_INVITE_ONLY;
				break;
			case 't':
				m.mode = CHAN_SET_TOPIC;
				break;
			case 'k':
				m.mode = CHAN_SET_KEY;
				break;
			case 'l':
				m.mode = CHAN_SET_LIMIT;
				break;
			case 'o':
				m.mode = CHAN_SET_OP;
				break;
			default :
				m.mode = ERROR_MODE;
				break;
		}
		if ((m.mode == CHAN_SET_KEY || m.mode == CHAN_SET_LIMIT || m.mode == CHAN_SET_OP) && argIndex < _args.size())
			m.arguments = _args[argIndex++];
		this->_mode.push_back(std::make_pair(true, m));
	}
}

/**
 * @brief Parsing of the mode command
 *
 * @return return the e_code if there is an error else return _PARSING_OK
 */
e_code Mode::checkArgs() {
	if (_args.size() < 2)
		return ERR_NEEDMOREPARAMS;
	if (_args.at(1).at(0) != '#') {
		WARNING_MSG("Invalid channel name for INVITE command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args.at(1).erase(0, 1);
	if (_cTarget == NULL) {
		WARNING_MSG("Channel not found for INVITE command");
		INFO_MSG("You can only invite users to channels you are in");
		return ERR_NOSUCHCHANNEL;
	}
	if (_args.size() == 2) {
		return RPL_CHANNELMODEIS;
	}
	checkMode();
	if (_mode.empty())
		return ERR_UNKNOWNMODE;
	for (size_t i = 0; i < _mode.size(); ++i)
	{
		const s_mode &m = _mode[i].second;
		if (m.mode == ERROR_MODE)
			return ERR_UNKNOWNMODE;
		if (m.mode == CHAN_SET_KEY || m.mode == CHAN_SET_LIMIT || m.mode == CHAN_SET_OP)
			if (m.arguments.empty())
				return ERR_NEEDMOREPARAMS;
		if (searchList(_cTarget->getOperators(), _sender->getName()) != NULL) {
			WARNING_MSG("You are not an operator in the channel for INVITE command");
			return ERR_CHANOPRIVSNEEDED;
		}
	}

	return _PARSING_OK;
}

/**
 * @brief Execute the invite command
 * @note To invite a peapol to join a channel (from an operator)
 */
void Mode::execute() {
	if (checkArgs() == _PARSING_OK) {
		ERROR_MSG("Invalid arguments for INVITE command (see warning message)");
		return;
	}
	// check how the com
}
