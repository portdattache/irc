/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/11 07:59:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "ft_irc.hpp"

class	Client;

void	sendMessage(Client *client, const std::string &msg);
void	sendError(Client &client, const std::string &code);
void	sendReply(Client &client, const std::string &code,
			const std::string &msg);

#endif