#include <iostream>
#include "core.hpp"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << CLR_RED << "Usage: " << argv[0] << " <port> <password>" << CLR_RESET << std::endl;
		return 1;
	}
	if (DEBUG) {
		std::cout << CLR_GREY << "Port:\t\t" << CLR_GREEN << argv[1] << CLR_RESET << std::endl;
		std::cout << CLR_GREY << "Password:\t" << CLR_GREEN << argv[2] << CLR_RESET << std::endl;
	}
	while (1)
		;
	return 0;
}
