/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:36:51 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:53:28 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "JoinCmd.hpp"
#include "Server.hpp"
#include "Utils.hpp"

void JoinCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;

	if (args.empty())
		return (sendError(client, ERR_NEEDMOREPARAMS));
	std::string chanName = args[0];
	chan = server.getChannel(chanName);
	if (!chan)
		chan = server.createChannel(chanName);
	chan->addMember(&client);
	chan->broadcast(":" + client.getNickname() + " JOIN " + chanName);
}
