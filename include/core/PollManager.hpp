#pragma once

#include <map>
#include <vector>
#include <string>

class PollManager {
public:
	PollManager();
	~PollManager();

    void addClient(int fd);
    void removeClient(int fd);
	void updateServer(int fd);
    void pollLoop(int server_fd);

private:

    std::vector<struct pollfd> _fds;
    std::map<int, std::string> _buffers;

};
