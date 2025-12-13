/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:54:35 by broboeuf          #+#    #+#             */
/*   Updated: 2025/12/13 08:29:23 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "PartCmd.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PartCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;

	// Verifie si ke client est enregistre
	if (!client.isRegistered())
		return (sendError(server, client, ERR_NOTREGISTERED, "PART", ""));
	// Verifie les parametres
	if (args.empty())
		return (sendError(server, client, ERR_NEEDMOREPARAMS, "PART", ""));
	const std::string channelName = args[0];
	chan = server.getChannel(channelName);
	if (!chan)
		return (sendError(server, client, ERR_NOSUCHCHANNEL, channelName, ""));
	if (!chan->isMember(client))
		return (sendError(server, client, ERR_NOTONCHANNEL, channelName, ""));
	// Broadcast announcement + espace manquant sur le PART #Channel
	std::string msg = ":" + client.getNickname() + "!" + client.getUsername()
		+ "@localhost PART " + channelName;
	chan->broadcast(msg);
	// On supprime le client du channel et de la liste d'operator si il l'est
	chan->removeMember(&client);
	chan->removeOperator(&client);
	// Supprimer le channel si vide
	if (chan->getMemberCount() == 0)
		server.removeChannel(channelName);
}
