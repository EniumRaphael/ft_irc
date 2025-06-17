/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/18 00:58:16 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "join.hpp"
#include "commands.hpp"
#include "logs.hpp"
#include <list>

using namespace cmd;

e_code Join::checkArgs() {
	if (_args.size() < 2 || _args[1].empty()) {
		WARNING_MSG("Not enough arguments for Join command");
		return ERR_NEEDMOREPARAMS;
	}
	if (_args[1][0] != '#') {
		WARNING_MSG("Invalid channel name for Join command");
		INFO_MSG("Channel names must start with a '#' character");
		return ERR_NOSUCHCHANNEL;
	} else
		_args[1].erase(0, 1);
	return _PARSING_OK;
}

/**
 * @brief Execute the join command
 * @note To join a new channel
 */

void Join::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for Join command (see warning message)");
		return;
	}

	// Récupérer la liste des channels par référence
	std::list<Channel*>& allChannels = _server->getChannelsList();

	// msgJoin, msg332, msg353
	
	// Vérifier si le channel existe déjà
	_cTarget = searchList(allChannels, _args.at(1));
	if (_cTarget == NULL) {
		// Le channel n'existe pas, on le crée
		_cTarget = new Channel(_args[1], _sender, 50, false); // false = public
		allChannels.push_back(_cTarget);

		// Ajout automatique du créateur dans le channel
		_cTarget->addUser(_sender);
		_cTarget->addOperator(_sender);

		std::string msgJoin = ":" + _sender->getPrefix() + " JOIN #" + _cTarget->getName() + "\r\n";
		std:: string msg332 = ":" + _sender->getPrefix() + " 332 " +  _sender->getNickname() + " #" + _cTarget->getName() + " :" + _cTarget->getTopic() + "\r\n";
		std::string msg353 = ":" + _sender->getPrefix() + " 353 " + _sender->getNickname() + " = #" + _cTarget->getName() + " :";
		for (std::list<User *>::iterator it = _cTarget->getUsers().begin(); it != _cTarget->getUsers().end(); ++it) {
			msg353 += (*it)->getNickname() + " ";
		}
		_sender->appendToWriteBuffer(msgJoin +  msg332 + msg353 + "\r\n");
		return;
	}

	// Si le channel est privé, vérifier que l'utilisateur est invité
	
	if (_cTarget->getNeedInvite() == true) {
		if (!searchList(_cTarget->getInvited(), _sender->getName())) {
			std::string msgErr = ":localhost 473 " + _sender->getNickname() + " #" + _cTarget->getName() + " :Cannot join channel (+i)\r\n";
			_sender->appendToWriteBuffer(msgErr);
			return;
		}
	}

	// Ajouter le user au channel
	_cTarget->addUser(_sender);

	// Envoyer le JOIN à tous les membres du channel
	std::string msgJoin = ":" + _sender->getPrefix() + " JOIN #" + _cTarget->getName() + "\r\n";
	std:: string msg332 = ":" + _sender->getPrefix() + " 332 " +  _sender->getNickname() + " #" + _cTarget->getName() + " :" + _cTarget->getTopic() + "\r\n";
	std::string msg353 = ":" + _sender->getPrefix() + " 353 " + _sender->getNickname() + " = #" + _cTarget->getName() + " :";
	for (std::list<User *>::iterator it = _cTarget->getUsers().begin(); it != _cTarget->getUsers().end(); ++it) {
		msg353 += (*it)->getNickname() + " ";
	}
	_cTarget->sendAllClientInAChannel(msgJoin + msg332 + msg353 + "\r\n", _sender);
}
