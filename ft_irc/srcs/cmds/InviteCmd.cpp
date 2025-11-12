/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:22:28 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:41:01 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void InviteCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	Client	*target;

	if (args.size() < 2)
		return (client.sendMessage(ERR_NEEDMOREPARAMS));
	const std::string nickname = args[0];
	const std::string channel = args[1];
	chan = server.getChannel(channel);
	if (!chan)
		return (client.sendMessage(ERR_NOSUCHCHANNEL));
	target = server.getClientByNick(nickname);
	if (!target)
		return (client.sendMessage(ERR_NOSUCHNICK));
	target->sendMessage(":" + client.getNickname() + " INVITE " + nickname + " "
		+ channel);
}
