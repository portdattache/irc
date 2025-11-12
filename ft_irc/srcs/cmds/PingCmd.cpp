/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:37:53 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 14:43:07 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PingCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	(void)server;
	(void)args;
	client.sendMessage("PONG\r\n");
}
