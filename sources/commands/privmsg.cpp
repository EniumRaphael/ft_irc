/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/24 14:02:33 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "privmsg.hpp"
#include "commands.hpp"
#include "logs.hpp"
#include "bonus.hpp"
#include <algorithm>

using namespace cmd;

// exemple:
// PRIVMSG #samy :salut 

e_code PrivMsg::checkArgs() {
	if (_args.size() < 3) {
		std::string msg461 = ":localhost 461 " + this->_sender->getNickname() + " " + this->_command + " :Not enough parameters\r\n";
		this->_sender->appendToWriteBuffer(msg461);
		return ERR_NEEDMOREPARAMS;
	}

	std::string target = _args.at(1);

	if (target[0] == '#') {
		target.erase(0, 1); // Enlève le '#'
		_cTarget = searchList(_server->getChannelsList(), target);
		if (_cTarget == NULL) {
			WARNING_MSG("Channel not found for PRIVMSG command");
			return ERR_NOSUCHCHANNEL;
		}
	} 
	else {
		_uTarget = searchList(_users, target);
		if (_uTarget == NULL || !_uTarget->isRegistered()) {
			WARNING_MSG("User not found or not registered");
			return ERR_NOSUCHNICK;
		}
	}
	return _PARSING_OK;
}

/**
 * @brief Execute the PrivMsg command
 * @note To send a private message to a user / a channel
 */

void PrivMsg::execute() {
	if (checkArgs() != _PARSING_OK) {
		ERROR_MSG("Invalid arguments for PRIVMSG command (see warning message)");
		return;
	}

	std::string target = _args.at(1);
	std::string content = _args.at(2);
	std::string msg = ":" + _sender->getPrefix() + " PRIVMSG " + target + " :" + content + "\r\n";

	//bonus msgBot
	std::string msgBot = ":bot!ircbot@localhost PRIVMSG " + target + " :📜 Liste des commandes disponibles :\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- JOIN #channel         → Rejoindre un canal\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- PART #channel         → Quitter un canal\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- PRIVMSG <cible> msg   → Envoyer un message\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- TOPIC #channel :txt   → Voir / modifier le topic\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- MODE #channel +o nick → Ajouter un opérateur\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- INVITE nick #channel  → Inviter un utilisateur\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- KICK #channel nick    → Éjecter un utilisateur\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- WHO / WHOIS           → Infos sur les utilisateurs\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- DCC SEND nick /PATH   → Transferer des fichiers à l'utilisateur\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- DCC GET /PATH         → Accepter le transfert des fichiers reçu\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- !emote                → Affiche la liste d'emoji\r\n";
				msgBot += ":bot!ircbot@localhost PRIVMSG " + target + " :- !help                 → Affiche cette aide\r\n";

	std::string msgEmote = ":bot!ircbot@localhost PRIVMSG " + target + " :           📜 Emote list :\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :😀😁😂😃😄😅😆😇😈😉😊😋😌😍😎😏\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :😐😑😒😓😔😕😖😗😘😙😚😛😜😝😞😟\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :😠😡😢😣😤😥😦😧😨😩😪😫😬😭😮😯\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :😰😱😲😳😴😵😶😷😸😹😺😻😼😽😾😿\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :🙀🙁🙂🙃🙄🙅🙆🙇🙈🙉🙊🙋🙌🙍🙎🙏\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :🤐🤑🤒🤓🤤🤔🤕🤖🤗🤘🤙🤚🤛🤜🤝🤟\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :💐💑💒💓💔💕💖💗💘💙💚💛💜💝💞💟\r\n";
				msgEmote += ":bot!ircbot@localhost PRIVMSG " + target + " :💠💡💢💣💤💥💦💧💨💩💪💫💬💭💯🤨\r\n";
	
	std::cout << "target = " << target << std::endl;
	// Envoi vers un channel
	if (target[0] == '#') {
		target.erase(0, 1);

		if (_cTarget) {
			if (BONUS && _cTarget->getBotChannel() && _args.at(2) == "!help")
				_sender->appendToWriteBuffer(msgBot);
			else if (BONUS && _cTarget->getBotChannel() && _args.at(2) == "!emote")
				_sender->appendToWriteBuffer(msgEmote);
			else
				_cTarget->sendAllClientInAChannel(msg, _sender);
		}
	}
	
	// Envoi vers un user
	const std::list<User *>& users = _server->getUsersList();

	for (std::list<User *>::const_iterator it = users.begin(); it != users.end(); ++it) {
		if ((*it)->getName() == target) {
			(*it)->appendToWriteBuffer(msg);
			break;
		}
	}
}
