/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:13 by omoudni           #+#    #+#             */
/*   Updated: 2025/05/22 17:30:00 by omoudni          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
    void pollLoop(int server_fd, std::vector<int> &newClients, std::vector<int> &disconnected, std::vector<std::pair<int, std::string> > &readyClients);

private:
    std::vector<struct pollfd> _fds;
};
