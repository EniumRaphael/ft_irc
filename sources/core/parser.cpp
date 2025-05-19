/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:48:52 by omoudni           #+#    #+#             */
/*   Updated: 2025/05/19 15:08:18 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include <iostream>

Parser::Parser(int argc, char* argv[]) : _port(0), _valid(false) {
    if (argc != 3) {
        _errorMsg = "Usage: ./ircserv <port> <password>";
        return;
    }
    _port = valid_port(argv[1]);
    if (_port == 0) {
        _errorMsg = "Error: Invalid port: " + std::string(argv[1]);
        return;
    }
    _password = argv[2];
    if (_password.empty()) {
        _errorMsg = "Error: Password cannot be empty";
        return;
    }
    for (size_t i = 0; i < _password.size(); ++i) {
        if (!isprint(_password[i])) {
            _errorMsg = "Error: Password contains non-printable characters";
            return;
        }
    }
    _valid = true;
}

bool Parser::isValid() const { return _valid; }
unsigned short int Parser::getPort() const { return _port; }
const std::string& Parser::getPassword() const { return _password; }
const std::string& Parser::getErrorMsg() const { return _errorMsg; }