/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:15:13 by omoudni           #+#    #+#             */
/*   Updated: 2025/05/20 17:22:59 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
