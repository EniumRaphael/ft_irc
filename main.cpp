#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	std::cout << "Port:" << argv[1] << std::endl;
	std::cout << "Password:" << argv[2] << std::endl;
	return 0;
}
