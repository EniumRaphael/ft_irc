/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:16:03 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/21 21:18:22 by omoudni          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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


// INCLUDES (not to repeat)
#include <stdexcept>
#include <iostream>
#include <string>
#include "user.hpp"
#include "PollManager.hpp"
#include "color.hpp"
#include "server.hpp"
#include "parser.hpp"

unsigned short int valid_port(char *input);
