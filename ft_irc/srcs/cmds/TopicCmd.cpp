/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:56:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:43:33 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Topic.hpp"
#include "ft_irc.hpp"

void TopicCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;

	if (args.empty())
		return (client.sendMessage(ERR_NEEDMOREPARAMS));
	const std::string channel = args[0];
	chan = server.getChannel(channel);
	if (!chan)
		return (client.sendMessage(ERR_NOSUCHCHANNEL));
	if (args.size() == 1)
		return (client.sendMessage(":" + server.getName() + " 332 "
				+ client.getNickname() + " " + channel + " :"
				+ chan->getTopic().getTopic()));
	const std::string newTopic = args[1];
	chan->getTopic().setTopic(newTopic, client.getNickname());
	chan->broadcast(":" + client.getNickname() + " TOPIC " + channel + " :"
		+ newTopic);
}
