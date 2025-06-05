/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:16:03 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/05 11:10:45 by rparodi          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#ifdef DEBUG
#define LOG std::endl << CLR_CYAN << "Debug: " << __FILE__ << ":" << __LINE__  << std::endl << CLR_RESET
#endif

enum e_code {
	//command for parsing
	_PARSING_OK                = 000,
    // Reply codes (RPL_*)
    RPL_WELCOME                = 001,  // “<nick> :Welcome to the Internet Relay Network <nick>!<user>@<host>”
    RPL_YOURHOST               = 002,  // “<nick> :Your host is <servername>, running version <ver>”
    RPL_CREATED                = 003,  // “<nick> :This server was created <date>”
    RPL_MYINFO                 = 004,  // “<nick> <servername> <version> <available_user_modes> <available_channel_modes>”
    RPL_BOUNCE                 = 005,  // “<nick> <feature> … :are available on this server”
    
    // Tracing and stats (200–211, 214, 219–221, 241–242, 250–255)
    RPL_TRACELINK              = 200,  // “Link <version & debug level> <destination> <next server> V<protocol version>”
    RPL_TRACECONNECTING        = 201,  // “Try. <class> <server>”
    RPL_TRACEHANDSHAKE         = 202,  // “H.S. <class> <server>”
    RPL_TRACEUNKNOWN           = 203,  // “???? <class> [<client IP address>]”
    RPL_TRACEOPERATOR          = 204,  // “Oper <class> <nick>”
    RPL_TRACEUSER              = 205,  // “User <class> <nick>”
    RPL_TRACESERVER            = 206,  // “Serv <class> <int>S <int>C <server> <nick!user@host>”
    RPL_TRACESERVICE           = 207,  // “Service <class> <name> <type> <active type>”
    RPL_TRACENEWTYPE           = 208,  // “<newtype> 0 <client name>”
    RPL_TRACECLASS             = 209,  // “Class <class> <count>`
    RPL_TRACERECONNECT         = 210,  // “Reconnect <class> <server> <port>”
    RPL_STATSLINKINFO          = 211,  // “Link <destination> <sendq> <sent messages> <sent bytes> <received messages> <received bytes> <time open>”
    
    RPL_STATSCOMMANDS          = 212,  // “<command> <count> <byte count> <remote count>”
    RPL_STATSCLINE             = 213,  // “C <host> * <name> <port> <class>”
    RPL_STATSNLINE             = 214,  // “N <host> * <name> <port> <class>”
    RPL_STATSILINE             = 215,  // “I <host> * <name> <port> <class>”
    RPL_STATSKLINE             = 216,  // “K <host> * <name> <port> <class>”
    RPL_STATSQLINE             = 217,  // “L <host> * <name> <port> <class>”
    RPL_STATSYLINE             = 218,  // “Y <class> <ping frequency> <connect frequency> <max sendq>”
    RPL_ENDOFSTATS             = 219,  // “<stats letter> :End of STATS report”
    
    RPL_UMODEIS                = 221,  // “<nick> <user modes>”
    
    RPL_STATSLLINE             = 241,  // “L <host> * <name> <port> <class>”
    RPL_STATSHLINE             = 242,  // “H <host> * <name> <port> <class>”
    RPL_STATSSLINE             = 243,  // “S <host> * <name> <port> <class>”
    RPL_STATSPING              = 244,  // “P <host> * <name> <port> <class>”
    RPL_STATSBLINE             = 245,  // “B <host> * <name> <port> <class>”
    RPL_ENDOFSTATS2            = 246,  // (Non standardisé, rarement utilisé)
    
    // Local users statistics (250–255)
    RPL_LUSERCLIENT            = 251,  // “There are <integer> users and <integer> invisible on <integer> servers”
    RPL_LUSEROP                = 252,  // “<integer> :operator(s) online”
    RPL_LUSERUNKNOWN           = 253,  // “<integer> :unknown connection(s)”
    RPL_LUSERCHANNELS          = 254,  // “<integer> :channels formed”
    RPL_LUSERME                = 255,  // “I have <integer> clients and <integer> servers”
    
    // Admin info (256–259)
    RPL_ADMINME                = 256,  // “<server> :Administrative info”
    RPL_ADMINLOC1              = 257,  // “<admin info>”
    RPL_ADMINLOC2              = 258,  // “<admin info>”
    RPL_ADMINEMAIL             = 259,  // “<admin email>”
    
    // User information (300–314, 315, 317–319, 369)
    RPL_NONE                   = 300,  // (Placeholder, pas toujours envoyé)
    RPL_AWAY                   = 301,  // “<nick> :<away message>”
    RPL_USERHOST               = 302,  // “:<reply>”
    RPL_ISON                   = 303,  // “:<names>”
    RPL_UNAWAY                 = 305,  // “<nick> :You are no longer marked as being away”
    RPL_NOWAWAY                = 306,  // “<nick> :You have been marked as being away”
    RPL_WHOISUSER              = 311,  // “<nick> <user> <host> * :<real name>”
    RPL_WHOISSERVER            = 312,  // “<nick> <server> :<server info>”
    RPL_WHOISOPERATOR          = 313,  // “<nick> :is an IRC operator”
    RPL_WHOISIDLE              = 317,  // “<nick> <integer> :seconds idle”
    RPL_ENDOFWHOIS             = 318,  // “<nick> :End of WHOIS list”
    RPL_WHOISCHANNELS          = 319,  // “<nick> :(<status>)<channel> …”
    RPL_WHOWASUSER             = 314,  // “<nick> <user> <host> * :<real name>”
    RPL_ENDOFWHOWAS            = 369,  // “<nick> :End of WHOWAS”
    
    // Channel listing (321–324)
    RPL_LISTSTART              = 321,  // “Channel :Users Name”
    RPL_LIST                   = 322,  // “<channel> <# visible> :<topic>”
    RPL_LISTEND                = 323,  // “:End of LIST”
    RPL_CHANNELMODEIS          = 324,  // “<channel> <mode> <mode params>”
    
    // Topic (331–332)
    RPL_NOTOPIC                = 331,  // “<channel> :No topic is set”
    RPL_TOPIC                  = 332,  // “<channel> :<topic>”
    
    // Invite and exception lists (341–347, 348–349)
    RPL_INVITING               = 341,  // “<channel> <nick>”
    RPL_SUMMONING              = 342,  // “<user> :Summoning user to IRC”
    RPL_INVITELIST             = 346,  // “<channel> <banid>”
    RPL_ENDOFINVITELIST        = 347,  // “<channel> :End of channel invite list”
    RPL_EXCEPTLIST             = 348,  // “<channel> <banid>”
    RPL_ENDOFEXCEPTLIST        = 349,  // “<channel> :End of channel exception list”
    
    // Version (351)
    RPL_VERSION                = 351,  // “<version>.<debuglevel> <server> :<comments>”
    
    // WHO (352–353, 315, 366)
    RPL_WHOREPLY               = 352,  // “<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>”
    RPL_ENDOFWHO               = 315,  // “<name> :End of WHO list”
    RPL_NAMREPLY               = 353,  // “<channel> :([@|+]<nick> )”
    RPL_ENDOFNAMES             = 366,  // “<channel> :End of NAMES list”
    
    // Links (364–365)
    RPL_LINKS                  = 364,  // “<mask> <server> :<hopcount> <server info>”
    RPL_ENDOFLINKS             = 365,  // “<mask> :End of LINKS list”
    
    // Ban list (367–368)
    RPL_BANLIST                = 367,  // “<channel> <banid>”
    RPL_ENDOFBANLIST           = 368,  // “<channel> :End of channel ban list”
    
    // Info (371–374)
    RPL_INFO                   = 371,  // “:<text>”
    RPL_ENDOFINFO              = 374,  // “:End of INFO list”
    
    // MOTD (375–376)
    RPL_MOTDSTART              = 375,  // “:- <server> Message of the day - ”
    RPL_MOTD                   = 372,  // “:- <text>”
    RPL_ENDOFMOTD              = 376,  // “<server> :End of MOTD command”
    
    // Operator (381–383)
    RPL_YOUREOPER              = 381,  // “<nick> :You are now an IRC operator”
    RPL_REHASHING              = 382,  // “<config file> :Rehashing”
    RPL_YOURESERVICE           = 383,  // “<servicename> <server> :<service info>”
    
    // Time (391)
    RPL_TIME                   = 391,  // “<server> :<time>”
    
    // Users (392–395)
    RPL_USERSSTART             = 392,  // “:UserID Terminal Host”
    RPL_USERS                  = 393,  // “:<username> <ttyline> <hostname>”
    RPL_ENDOFUSERS             = 394,  // “:End of users”
    RPL_NOUSERS                = 395,  // “:Nobody logged in”
    
    // Error codes (ERR_*)
    ERR_NOSUCHNICK             = 401,  // “<nick> :No such nick/channel”
    ERR_NOSUCHSERVER           = 402,  // “<server name> :No such server”
    ERR_NOSUCHCHANNEL          = 403,  // “<channel name> :No such channel”
    ERR_CANNOTSENDTOCHAN       = 404,  // “<channel> :Cannot send to channel”
    ERR_TOOMANYCHANNELS        = 405,  // “<channel> :You have joined too many channels”
    ERR_WASNOSUCHNICK          = 406,  // “<nick> :There was no such nick”
    ERR_TOOMANYTARGETS         = 407,  // “<target> :Duplicate recipients. No message delivered”
    ERR_NOSUCHSERVICE          = 408,  // “<service name> :No such service                                 ”
    ERR_NOORIGIN               = 409,  // “:No origin specified”
    ERR_NOREC                  = 411,  // “:No recipient given (<command>)”
    ERR_NOTEXTTOSEND           = 412,  // “:No text to send”
    ERR_NOTOPLEVEL             = 413,  // “<mask> :No toplevel domain specified”
    ERR_WILDTOPLEVEL           = 414,  // “<mask> :Wildcard in toplevel domain”
    ERR_BADMASK                = 415,  // “<mask> :Bad Server/host mask”
    ERR_UNKNOWNCOMMAND         = 421,  // “<command> :Unknown command”
    ERR_NOMOTD                 = 422,  // “:MOTD File is missing”
    ERR_NOADMININFO            = 423,  // “<server> :No administrative info available”
    ERR_FILEERROR              = 424,  // “:File error doing <file op> on <file>”
    ERR_NONICKNAMEGIVEN        = 431,  // “:No nickname given”
    ERR_ERRONEUSNICKNAME       = 432,  // “<nick> :Erroneous nickname”
    ERR_NICKNAMEINUSE          = 433,  // “<nick> :Nickname is already in use”
    ERR_NICKCOLLISION          = 436,  // “<nick> :Nickname collision KILL”
    ERR_UNAVAILRESOURCE        = 437,  // “<nick/channel> :Nick/channel is temporarily unavailable”
    ERR_USERNOTINCHANNEL       = 441,  // “<nick> <channel> :They aren't on that channel”
    ERR_NOTONCHANNEL           = 442,  // “<channel> :You're not on that channel”
    ERR_USERONCHANNEL          = 443,  // “<user> <channel> :is already on channel”
    ERR_NOLOGIN                = 444,  // “<user> :User not logged in”
    ERR_SUMMONDISABLED         = 445,  // “:SUMMON has been disabled”
    ERR_USERSDISABLED          = 446,  // “:USERS has been disabled”
    ERR_NOTTERED               = 451,  // “:You have not registered”
    ERR_NEEDMOREPARAMS         = 461,  // “<command> :Not enough parameters”
    ERR_ALREADYREGISTERED      = 462,  // “:You may not reregister”
    ERR_NOPERMFORHOST          = 463,  // “:Your host isn't among the privileged”
    ERR_PASSWDMISMATCH         = 464,  // “:Password incorrect”
    ERR_YOUREBANNEDCREEP       = 465,  // “:You are banned from this server”
    ERR_YOUWILLBEBANNED        = 466,  // “<channel> :You will be banned from this channel”
    ERR_KEYSET                 = 467,  // “<channel> :Channel key already set”
    ERR_CHANNELISFULL          = 471,  // “<channel> :Cannot join channel (+l)”
    ERR_UNKNOWNMODE            = 472,  // “<char> :is unknown mode char to me”
    ERR_INVITEONLYCHAN         = 473,  // “<channel> :Cannot join channel (+i)”
    ERR_BANNEDFROMCHAN         = 474,  // “<channel> :Cannot join channel (+b)”
    ERR_BADCHANNELKEY          = 475,  // “<channel> :Cannot join channel (+k)”
    ERR_BADCHANMASK            = 476,  // “<channel> :Bad Channel Mask”
    ERR_NOCHANMODES            = 477,  // “<channel> :Channel doesn't support modes”
    ERR_BANLISTFULL            = 478,  // “<channel> <banid> :Channel list is full”
    ERR_NOPRIVILEGES           = 481,  // “:Permission Denied- You're not an IRC operator”
    ERR_CHANOPRIVSNEEDED       = 482,  // “<channel> :You're not channel operator”
    ERR_CANTKILLSERVER         = 483,  // “:You can't kill a server!”
    ERR_RESTRICTED             = 484,  // “:Your connection is restricted!”
    ERR_UNIQOPPRIVSNEEDED      = 485,  // “<channel> :You're not the original channel operator”
    ERR_NOOPERHOST             = 491,  // “:No O-lines for your host”
    ERR_UMODEUNKNOWNFLAG       = 501,  // “:Unknown MODE flag”
    ERR_USERSDONTMATCH         = 502   // “:Cannot change mode for other users”
};

#ifndef DEBUG
#define DEBUG 0
#define LOG ""
#endif

enum e_state {
    ERROR = 0,
    CMD,
    MSG
    };


// INCLUDES (not to repeat)
#include <stdexcept>
#include <iostream>
#include <string>
#include "user.hpp"
#include "PollManager.hpp"
#include "color.hpp"
#include "server.hpp"
#include "parser.hpp"

unsigned short int valid_port(char *input);
