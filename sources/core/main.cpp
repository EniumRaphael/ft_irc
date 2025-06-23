/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:03:13 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/23 14:38:53 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.hpp"
#include <iostream>
#include "server.hpp"
#include <signal.h>



int main(int argc, char *argv[]) {
    Parser parser(argc, argv);
    if (!parser.isValid()) {
        std::cerr << CLR_RED << parser.getErrorMsg() << CLR_RESET << std::endl;
        return 1;
    }
    Server server(parser.getPort(), parser.getPassword());
    server.showInfo();
    server.start();
    return 0;
}
