/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:34:30 by rparodi           #+#    #+#             */
/*   Updated: 2025/06/17 17:36:11 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

/**
 * @brief Return the element searched in a list
 *
 * @tparam T Type of the list have to be search (have to get an getName() method)
 * @param list list to search in
 * @param name name of the element to search
 * @return pointer to the element found or NULL if not found
 */
template <typename T>
T cmd::searchList(const std::list<T> &list, const std::string &name) {
	for (typename std::list<T>::const_iterator it = list.begin(); it != list.end(); ++it) {
		if ((*it)->getName() == name)
			return *it;
	}
	return NULL;
}
