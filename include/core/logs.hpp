/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:25:58 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/26 18:08:50 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "color.hpp"

#define DEBUG_MSG(str) std::cerr << CLR_CYAN << "\tDebug: " << str << "(" << __FILE__ << ":" << __LINE__ << ")" << CLR_RESET << std::endl;
#define ERROR_MSG(str) std::cerr << CLR_RED << "\tError: " << str << "(" << __FILE__ << ":" << __LINE__ << ")" << CLR_RESET << std::endl;
#define WARNING_MSG(str) std::cerr << CLR_YELLOW << "\tWarning: " << str << "(" << __FILE__ << ":" << __LINE__ << ")" << CLR_RESET << std::endl;
#define INFO_MSG(str) std::cerr << CLR_GREY << "\tInfo: " << str << "(" << __FILE__ << ":" << __LINE__ << ")" << CLR_RESET << std::endl;
#define SUCCESS_MSG(str) std::cerr << CLR_GREEN << "\tSuccess: " << str << "(" << __FILE__ << ":" << __LINE__ << ")" << CLR_RESET << std::endl;


#ifndef DEBUG
#define DEBUG 0
#define LOG ""
#endif
