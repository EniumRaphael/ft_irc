/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:57:49 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/20 22:13:41 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include "color.hpp"

class User {
	private:
		int _fd;
		bool _registered;
		std::string _nickname;
		std::string _hostname;
		std::string _read_buffer;
		std::string _write_buffer;
	public:
		int getFd() const;
		bool isReadyToSend() const;
		bool isRegistered() const;
		std::string getNickname() const;
		std::string extractFullCommand();
		void appendToReadBuffer(const std::string &data);
		void appendToWriteBuffer(const std::string &data);
		void setNickname(const std::string &nickname);
};
