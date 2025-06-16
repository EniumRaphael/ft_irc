/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:37:12 by omoudni           #+#    #+#             */
/*   Updated: 2025/06/16 18:36:36 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.hpp"
#include <unistd.h>

// Constructor
User::User(short unsigned int fd) : _fd(fd), _registered(false), _hasNick(false), _hasUser(false), \
    _hasPass(false), _passReceived(false), _passIsValid(false) {}

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
}

// Check registration
void User::checkRegistration()
{
    if (_registered)
        return;
    if (_hasNick && _hasUser && _passReceived && _passIsValid)
    {
        _registered = true;
        std::string msg = ":localhost 001 " + _nickname +
                          " :Welcome to the IRC server " + getPrefix() + "\r\n";
        appendToWriteBuffer(msg);
    }
    else if (_hasNick && _hasUser && _passReceived && !_passIsValid)
    {
        std::string msg = ":localhost 464 * :Password incorrect\r\n";
        appendToWriteBuffer(msg);
    }
    else if (_hasNick && _hasUser && !_passReceived)
    {
        std::string msg = ":localhost 451 * :You must send PASS to register\r\n";
        appendToWriteBuffer(msg);
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

std::string User::getPrefix() const {
	return _nickname + "!" + _username + "@localhost";
}
