/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:36:51 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/27 23:40:34 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "JoinCmd.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Topic.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void JoinCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	bool	isNewChannel;

	// Verifie si le client est enregistrer
	if (!client.isRegistered())
		return (sendError(server, client, ERR_NOTONCHANNEL, "JOIN",
				"You have not registered"));
	// Verifie les parametres
	if (args.empty())
		return (sendError(server, client, ERR_NEEDMOREPARAMS, "JOIN",
				"Not enough parameters"));
	std::string chanName = args[0];
	std::string key = (args.size() > 1) ? args[1] : "";
	// Verifie le nom du channel et le creer si il n'existe pas
	chan = server.getChannel(chanName);
	isNewChannel = false;
	if (!chan)
	{
		chan = server.createChannel(chanName);
		isNewChannel = true;
	}
	// On recupere le mode du channel et on check +i, +k, +l
	Mode &mode = chan->getMode();
	// +i (invite only)
	if (mode.isInviteOnly() && !chan->isMember(client)
		&& !chan->isInvited(client))
		return (sendError(server, client, ERR_INVITEONLYCHAN, chanName,
				"Channel is invite-only"));
	// +k (key)
	if (mode.hasKey() && !mode.checkKey(key))
		return (sendError(server, client, ERR_BADCHANNELKEY, chanName,
				"Incorrect channel key"));
	// +l (limit)
	if (mode.hasLimit() && chan->getMemberCount() >= mode.getLimit())
		return (sendError(server, client, ERR_CHANNELISFULL, chanName,
				"Channel is full"));
	// Ajouter le membre
	chan->addMember(&client);
	// Si premier membre du channel, lui donner le role d'operator
	if (isNewChannel)
		chan->addOperator(&client);
	// Supprimer l'invit si elle existait
	if (chan->isInvited(client))
		chan->removeInvitation(&client);
	// Message JOIN a tous le membres
	std::string joinMsg = ":" + client.getNickname() + " JOIN " + chanName;
	chan->broadcast(joinMsg);
	// Envoyer le topic
	if (!chan->getTopic().getTopic().empty())
		sendReply(server, client, RPL_TOPIC, chanName,
			chan->getTopic().getTopic());
	else
		sendReply(server, client, RPL_NOTOPIC, chanName, "No topic is set");
	// Envoyer la liste des membres
	std::string names;
	for (Client *c : chan->getMembers())
	{
		if (chan->isOperator(*c))
			names += "@" + c->getNickname() + " ";
		else
			names += c->getNickname() + " ";
	}
	sendReply(server, client, RPL_NAMREPLY, "= " + chanName, names);
	sendReply(server, client, RPL_ENDOFNAMES, chanName, "End of NAMES list");
}
