/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:47:46 by omoudni           #+#    #+#             */
/*   Updated: 2025/05/19 15:14:31 by omoudni          ###   ########.fr       */
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