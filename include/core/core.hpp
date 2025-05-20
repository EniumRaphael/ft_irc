/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:16:03 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/20 17:23:41 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef DEBUG
#define LOG std::endl << CLR_CYAN << "Debug: " << __FILE__ << ":" << __LINE__  << std::endl << CLR_RESET
#endif



#ifndef DEBUG
#define DEBUG 0
#define LOG ""
#endif

enum e_state {
    ERROR = 0,
    CMD,
    MSG
    };
    

#include "PollManager.hpp"
#include "color.hpp"
#include "server.hpp"
#include "parser.hpp"

unsigned short int valid_port(char *input);
