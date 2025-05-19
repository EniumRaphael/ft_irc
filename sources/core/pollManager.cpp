/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:48 by omoudni           #+#    #+#             */
/*   Updated: 2025/05/19 20:21:11 by omoudni          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pollManager.hpp"
#include <algorithm>

PollManager::PollManager() {}

void PollManager::addFd(int fd, short events) {
    struct pollfd pfd = {fd, events, 0};
    _fds.push_back(pfd);
    _fd_events[fd] = events;
}

void PollManager::removeFd(int fd) {
    for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ) {
        if (it->fd == fd)
            it = _fds.erase(it);
        else
            ++it;
    }
    _fd_events.erase(fd);
}

void PollManager::updateFd(int fd, short events) {
    for (size_t i = 0; i < _fds.size(); ++i) {
        if (_fds[i].fd == fd) {
            _fds[i].events = events;
            break;
        }
    }
    _fd_events[fd] = events;
}

int PollManager::pollEvents(int timeout) {
    return poll(_fds.data(), _fds.size(), timeout);
}

const std::vector<struct pollfd>& PollManager::getFds() const {
    return _fds;
}