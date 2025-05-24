#include "PollManager.hpp"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <cstdlib>

PollManager::PollManager() {}

PollManager::~PollManager()
{
    for (size_t i = 0; i < _fds.size(); ++i)
    {
        close(_fds[i].fd);
    }
}

void PollManager::pollLoop(int server_fd, std::vector<int> &newClients, std::vector<int> &disconnected, std::vector<std::pair<int, std::string> > &readyClients)
{
    int poll_count = poll(&_fds[0], _fds.size(), -1);
    if (poll_count == -1)
    {
        std::cerr << "poll error\n"
                  << std::endl;
        return;
    }
    for (size_t i = 0; i < _fds.size(); ++i)
    {
        short unsigned fd = _fds[i].fd;
        if ((fd == server_fd) && (_fds[i].revents & POLLIN))
        {
            int client_fd = accept(server_fd, NULL, NULL);
            if (client_fd == -1)
            {
                std::cerr << "Error accept()" << std::endl;
                continue;
            }
            addClient(client_fd);
            newClients.push_back(client_fd);
        }
        else if (_fds[i].revents & POLLIN)
        {
            char buffer[1024];
            ssize_t bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
            if (bytes > 0)
            {
                buffer[bytes] = '\0';
                readyClients.push_back(std::make_pair(fd, std::string(buffer)));
                std::cout << "Received data from fd " << fd << ": " << buffer << std::endl;
                std::cout << std::flush;
            }
            else
            {
                removeClient(fd);
                disconnected.push_back(fd);
                --i;
            }
        }
    }
    // }
}

void PollManager::addClient(short unsigned fd)
{
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    _fds.push_back(pfd);
    std::cout << "Client connected (fd " << fd << ")" << std::endl;
}

void PollManager::removeClient(short unsigned fd)
{
    for (size_t i = 0; i < _fds.size(); ++i)
    {
        if (_fds[i].fd == fd)
        {
            _fds.erase(_fds.begin() + i);
            break;
        }
    }
    close(fd);
    std::cout << "Client disconnected (fd " << fd << ")" << std::endl;
}

void PollManager::setServerFd(int fd)
{
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    _fds.push_back(pfd);
}
