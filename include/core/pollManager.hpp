/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:13 by omoudni           #+#    #+#             */
/*   Updated: 2025/05/19 19:25:45 by omoudni          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once
#include <vector>
#include <poll.h>
#include <map>

class PollManager {
private:
    std::vector<struct pollfd> _fds;
    std::map<int, short> _fd_events; // fd -> event

public:
    PollManager();
    void addFd(int fd, short events);
    void removeFd(int fd);
    void updateFd(int fd, short events);
    int pollEvents(int timeout = -1);
    const std::vector<struct pollfd>& getFds() const;
};