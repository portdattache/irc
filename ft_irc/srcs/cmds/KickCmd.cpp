/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:31:57 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:40:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void KickCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	Client	*victim;

	if (args.size() < 2)
		return (client.sendMessage(ERR_NEEDMOREPARAMS));
	const std::string channel = args[0];
	const std::string target = args[1];
	chan = server.getChannel(channel);
	if (!chan)
		return (client.sendMessage(ERR_NOSUCHCHANNEL));
	victim = server.getClientByNick(target);
	if (!victim)
		return (client.sendMessage(ERR_NOSUCHNICK));
	chan->broadcast(":" + client.getNickname() + " KICK " + channel + " "
		+ target);
	chan->removeMember(victim);
}
