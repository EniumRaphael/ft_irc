/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:34:11 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/24 12:34:12 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "core.hpp"
#include <string>

class Parser {
private:
    unsigned short int _port;
    std::string _password;
    bool _valid;
    std::string _errorMsg;

public:
    Parser(int argc, char* argv[]);
    bool isValid() const;
    unsigned short int getPort() const;
    const std::string& getPassword() const;
    const std::string& getErrorMsg() const;
};      
