/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:37:12 by omoudni           #+#    #+#             */
/*   Updated: 2025/06/18 01:19:52 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.hpp"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

// Constructor
User::User(short unsigned int fd, PollManager& poll) : _fd(fd), _registered(false), _hasNick(false), _hasUser(false), \
    _hasPass(false), _passReceived(false), _passIsValid(false), _poll(poll) {}

/**
 * @brief Getter for the fd
 *
 * @return the fd of the user
 */
short unsigned int User::getFd() const { return this->_fd; }

/**
 * @brief Getter for the nickname of the user
 *
 * @return the actual nickname of the user
 */
std::string User::getName() const {
	return this->_nickname;
}

void User::setUsername(const std::string &username) {
    _username = username;
    _hasUser = true;
}

// Setter for nickname (with basic checks)
void User::setNickname(const std::string &nickname) {
    if (nickname.empty()) {
        throw std::invalid_argument("Nickname cannot be empty");
    } else if (nickname == "anonymous") {
        throw std::invalid_argument("Nickname cannot be 'anonymous'");
	} else if (nickname.length() > 9) {
        throw std::length_error("Nickname is too long");
    } else if (nickname == _nickname) {
        throw std::invalid_argument("The nickname is the same");
    } else {
        _nickname = nickname;
        _hasNick = true;
    }
}

/**
 * @brief Setter to register a user
 */
void User::setRegistered() {
	this->_registered = true;
}

// Registration state
bool User::isRegistered() const
{
    return _registered;
}

// Append to read buffer
void User::appendToReadBuffer(const std::string &data)
{
    _read_buffer += data;
}

// Append to write buffer
void User::appendToWriteBuffer(const std::string &data)
{
    _write_buffer += data;
    _poll.setWritable(_fd, true);
}

// Check registration
void User::checkRegistration()
{
    if (_registered)
        return;
    if (_hasNick && _hasUser && _passReceived && _passIsValid)
    {
        _registered = true;
        resolveHostInfo();
        std::string msg001 = ":localhost 001 " + _nickname +
                          " :Welcome to the IRC server " + getPrefix() + "\r\n";
        appendToWriteBuffer(msg001);
    }
    else if (_hasNick && _hasUser && _passReceived && !_passIsValid)
    {
        std::string msg464 = ":localhost 464 * :Password incorrect\r\n";
        appendToWriteBuffer(msg464);
    }
    else if (_hasNick && _hasUser && !_passReceived)
    {
        std::string msg451 = ":localhost 451 * :You must send PASS to register\r\n";
        appendToWriteBuffer(msg451);
    }
}

// Check if the user is ready to send
bool User::isReadyToSend() const
{
    return !_write_buffer.empty();
}

// Extract full command from read buffer
std::string User::extractFullCommand() {
    size_t pos = _read_buffer.find("\r\n");
    if (pos == std::string::npos)
        pos = _read_buffer.find("\n"); // fallback

    if (pos != std::string::npos) {
        std::string command = _read_buffer.substr(0, pos);
        if (_read_buffer.substr(pos, 2) == "\r\n")
            _read_buffer.erase(0, pos + 2);
        else
            _read_buffer.erase(0, pos + 1);
        return command;
    }
    return "";
}

void User::setHasNick(bool value) { _hasNick = value; }

void User::setHasUser(bool value) { _hasUser = value; }

void User::setHasPass(bool value) { _hasPass = value; }

void User::setPassReceived(bool value) { _passReceived = value; }

void User::setPassIsValid(bool value) { _passIsValid = value; }

bool User::getHasPass() const { return _hasPass; }

std::string User::getNickname() const { return _nickname; }

bool User::hasDataToSend() const { return !_write_buffer.empty(); }

std::string User::getWriteBuffer() const { return _write_buffer; }

void User::clearWriteBuffer() { _write_buffer.clear(); }

std::string User::getPrefix() const { return _nickname + "!" + _username + "@" + _hostname; }

std::string User::getUsername() const { return _username; }

const std::string& User::getHostname() const { return _hostname; }

const std::string& User::getIpAddress() const { return _ipAdress; }

void User::setHostname(const std::string &hostname) { _hostname = hostname; }

void User::setIpAddress(const std::string &ip) { _ipAdress = ip; }

void User::resolveHostInfo()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	if (getpeername(_fd, (struct sockaddr*)&addr, &len) == -1)
	{
		std::cerr << "getpeername failed for fd " << _fd << std::endl;
		return;
	}

	_ipAdress = std::string(inet_ntoa(addr.sin_addr));

	struct hostent* host = gethostbyaddr((const void*)&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);
	if (host)
		_hostname = std::string(host->h_name);
	else
		_hostname = _ipAdress;
}

void User::setRealname(const std::string &realname) { _realname = realname; }

std::string User::getRealname(void) const { return _realname; }
