/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:22:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:42:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void NickCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	if (args.empty())
		return (client.sendMessage(ERR_NOSUCHNICK));
	std::string newNick = args[0];
	if (server.getClientByNick(newNick))
		return (client.sendMessage(ERR_NICKNAMEINUSE));
	client.setNickname(newNick);
	if (client.hasNickname() && !client.isRegistered())
		client.Registered();
}
