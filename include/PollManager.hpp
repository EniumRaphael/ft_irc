/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:13 by omoudni           #+#    #+#             */
/*   Updated: 2025/06/18 01:26:38 by sben-tay         ###   ########.fr       */
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
