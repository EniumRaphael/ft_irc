/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:29:48 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/02 23:04:53 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "logs.hpp"
#include "pong.hpp"
#include <ctime>

using namespace cmd;

/**
 * @brief Execute the Pong
 * @note answer to PING command (managed by the server)
 */
clock_t Pong::answer(clock_t start) {
	return (start - (clock() / CLOCKS_PER_SEC));
}
