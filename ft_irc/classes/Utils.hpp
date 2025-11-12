/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 11:59:25 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "ft_irc.hpp"

class	Client;

void	sendError(Client &client, const std::string &code);
void	sendReply(Client &client, const std::string &code,
			const std::string &msg);

#endif