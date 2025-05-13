/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:16:03 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/13 11:59:01 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef DEBUG
#define LOG std::endl << CLR_CYAN << "[DEBUG] " << __FILE__ << ":" << __LINE__  << std::endl << CLR_RESET
#endif

#ifndef DEBUG
#define DEBUG 0
#define LOG ""
#endif

#include "color.hpp"
#include "server.hpp"

unsigned short int valid_port(char *input);
