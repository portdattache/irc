/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:31:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 11:02:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void	sendError(Client &client, const std::string &code)
{
	sendMessage(&client, ":" + client.getNickname() + " " + code);
}

void	sendReply(Client &client, const std::string &code,
		const std::string &msg)
{
	sendMessage(&client, ":" + client.getNickname() + " " + code + " " + msg);
}
