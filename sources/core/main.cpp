/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:03:13 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/19 15:02:41 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.hpp"
#include <iostream>

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
