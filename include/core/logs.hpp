/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:25:58 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/15 12:38:10 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "color.hpp"

#define DEBUG_MSG(str) "print_debug(str, __FILE__, __LINE__)"
#define ERROR_MSG(str) "print_error(str, __FILE__, __LINE__)"
#define WARNING_MSG(str) "print_warning(str, __FILE__, __LINE__)"
#define INFO_MSG(str) "print_info(str, __FILE__, __LINE__)"
#define SUCCESS_MSG(str) "print_success(str, __FILE__, __LINE__)"


#ifndef DEBUG
#define DEBUG 0
#define LOG ""
#endif

void print_debug(const char *str, const char *file, int line);
void print_error(const char *str, const char *file, int line);
void print_warning(const char *str, const char *file, int line);
void print_info(const char *str, const char *file, int line);
void print_success(const char *str, const char *file, int line);
