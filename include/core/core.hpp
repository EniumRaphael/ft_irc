/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42paris.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:16:03 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/19 15:07:26 by omoudni          ###   ########.fr       */
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

#include "color.hpp"
#include "server.hpp"
#include "parser.hpp"

unsigned short int valid_port(char *input);
