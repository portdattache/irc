/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:35:59 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 21:53:02 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PrivMsgCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	Client	*to;

	if (args.size() < 2)
		return sendError(server, client, ERR_NEEDMOREPARAMS, "PRIVMSG", "Not enough parameters");

	std::string target = args[0];
	std::string message = args[1];
	if (target[0] == '#')
	{
		chan = server.getChannel(target);
		if (!chan)
			return sendError(server, client, ERR_NOSUCHCHANNEL, args[0], "No such channel");
		chan->broadcast(":" + client.getNickname() + " PRIVMSG " + target + " :"
			+ message);
	}
	else
	{
		to = server.getClientByNick(target);
		if (!to)
			return sendError(server, client, ERR_NOSUCHNICK, args[0], "No such nick");
		to->sendMessage(":" + client.getNickname() + " PRIVMSG " + target + " :"
			+ message);
	}
}
