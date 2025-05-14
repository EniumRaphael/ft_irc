/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:03:13 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/14 23:17:03 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << CLR_RED << "Usage: " << argv[0] << " <port> <password>" << CLR_RESET << std::endl;
		return 1;
	}
	unsigned short int tmp_port = valid_port(argv[1]);
	if (tmp_port == 0) {
		std::cerr << CLR_RED << "Error: Invalid port: " << argv[1] << CLR_RESET << std::endl;
		return 1;
	}
    Server server(tmp_port, argv[2]);
    server.showInfo();
    server.start();
    return 0;
}
