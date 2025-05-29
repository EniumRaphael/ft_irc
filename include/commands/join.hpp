/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:17:31 by rparodi           #+#    #+#             */
/*   Updated: 2025/05/26 22:43:47 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commands.hpp"

class cmd::Join : public ACommand {
	public:
		virtual void execute(void);
		virtual bool checkArgs();
};
