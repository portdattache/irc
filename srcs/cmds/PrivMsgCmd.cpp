/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:35:59 by bcaumont          #+#    #+#             */
/*   Updated: 2025/12/01 17:58:42 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "PrivMsgCmd.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PrivMsgCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	Client	*to;

	// Verifie si le client est enrigistre
	if (!client.isRegistered())
		return (sendError(server, client, ERR_NOTONCHANNEL, "PRIVMSG",
				"You have not registered"));
	// Verifie les arguments: Cible + message
	if (args.size() < 2)
		return (sendError(server, client, ERR_NOTEXTTOSEND, "PRIVMSG",
				"No text to send"));
	// On recupere la target
	std::string target = args[0];
	// Recomposer le message au cas ou il y a plusieurs mots
	std::string message;
	for (size_t i = 1; i < args.size(); ++i)
	{
		if (i > 1)
			message += " ";
		message += args[i];
	}
	if (!message.empty() && message[0] == ':')
		message = message.substr(1);
	if (message.empty())
		return (sendError(server, client, ERR_NOTEXTTOSEND, "PRIVMSG",
				"No text to send"));
	if (!target.empty() && target[0] == '#')
	{
		chan = server.getChannel(target);
		if (!chan)
			return (sendError(server, client, ERR_NOSUCHCHANNEL, target,
					"No such channel"));
		if (!chan->isMember(client))
			return (sendError(server, client, ERR_CANNOTSENDTOCHAN, target,
					"Cannot send to channel"));
		std::string msg = ":" + client.getNickname() + " PRIVMSG " + target
			+ " :" + message;
		chan->broadcast(msg);
	}
	else
	{
		to = server.getClientByNick(target);
		if (!to)
			return (sendError(server, client, ERR_NOSUCHNICK, target,
					"No such nick"));
		std::string msg = ":" + client.getNickname() + " PRIVMSG " + target
			+ " :" + message;
		to->sendMessage(msg);
	}
}
