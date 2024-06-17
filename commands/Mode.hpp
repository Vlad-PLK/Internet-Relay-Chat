/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:25:42 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/16 22:47:17 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
#define MODE_HPP
#include "../Command.hpp"

class ModeTool
{
	public:
		ModeTool();
		~ModeTool();

		std::string              modes;
		std::vector<std::string> modes_arg;
		std::vector<std::string> sign;
		std::string 			 prev;
		std::string				 current;
		std::string				 tmp_mode;
		std::string				 tmp_sign;
		bool 					 add;
};

#endif