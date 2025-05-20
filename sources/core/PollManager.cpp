#include "PollManager.hpp"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <cstdlib>

PollManager::PollManager() {}

PollManager::~PollManager() {
	for (size_t i = 0; i < _fds.size(); ++i) {
		close(_fds[i].fd);
	}
}

void PollManager::pollLoop(int server_fd) {

	struct pollfd server_pollfd;
    server_pollfd.fd = server_fd;
    server_pollfd.events = POLLIN;
    _fds.push_back(server_pollfd);

    std::cout << "Serveur prêt à accepter des connexions..." << std::endl;

    while (true) {
        int poll_count = poll(&_fds[0], _fds.size(), -1);
        if (poll_count == -1) {
            std::cerr << "poll error\n" << std::endl;
            continue;
        }
        for (size_t i = 0; i < _fds.size(); ++i) {
            int fd = _fds[i].fd;

            if ((fd == server_fd) && (_fds[i].revents & POLLIN)) {
                int client_fd = accept(server_fd, NULL, NULL);
                if (client_fd == -1) {
                    std::cerr << "Error accept()" << std::endl;
                    continue;
                }
                addClient(client_fd);
            }
            else if (_fds[i].revents & POLLIN) {
                char buffer[1024];
                ssize_t bytes = recv(fd, buffer, sizeof(buffer) -1, 0);
                if (bytes > 0) {
                    buffer[bytes] = '\0';
                    _buffers[fd] += buffer;
                    std::cout << "Client " << fd << " send : " << buffer;
                } else {
                    std::cout << "Client " << fd << " disconected." << std::endl;
                    // removeClient(fd);
                    --i;
                }
            }
        }
    }
}

void PollManager::addClient(int fd) {
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    _fds.push_back(pfd);
    _buffers[fd] = "";
    std::cout << "Client connecté (fd " << fd << ")" << std::endl;
}

void PollManager::removeClient(int fd) {
    for (size_t i = 0; i < _fds.size(); ++i) {
        if (_fds[i].fd == fd) {
            _fds.erase(_fds.begin() + i);
            break;
        }
    }
    _buffers.erase(fd);
    close(fd);
    std::cout << "Client retiré (fd " << fd << ")" << std::endl;
}
