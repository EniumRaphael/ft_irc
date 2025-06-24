/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:33:07 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/24 12:33:09 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <string>

class PollManager
{
public:
    PollManager();
    ~PollManager();

    void setServerFd(int fd);
    void addClient(short unsigned fd);
    void removeClient(short unsigned fd);
    void updateServer(short unsigned fd);
    void pollLoop(int server_fd, std::vector<int> &newClients, std::vector<int> &disconnected, std::vector<std::pair<int, std::string> > &readyClients, std::vector<int> &readyToWrite);
    void setWritable(short unsigned fd, bool enable);

private:
    std::vector<struct pollfd> _fds;
};
