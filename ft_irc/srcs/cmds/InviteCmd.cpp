/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:22:28 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 20:53:29 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCmd.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void InviteCmd::execute(Server &server, Client &client,
                        const std::vector<std::string> &args)
{
    if (!client.isRegistered())
        return sendError(server, client, ERR_NOTONCHANNEL, "INVITE",
                         "You are not registered");

    if (args.size() < 2)
        return sendError(server, client, ERR_NEEDMOREPARAMS, "INVITE",
                         "Not enough parameters");

    const std::string nickname = args[0];
    const std::string channelName = args[1];

    Channel *chan = server.getChannel(channelName);
    if (!chan)
        return sendError(server, client, ERR_NOSUCHCHANNEL, channelName,
                         "No such channel");

    Client *target = server.getClientByNick(nickname);
    if (!target)
        return sendError(server, client, ERR_NOSUCHNICK, nickname,
                         "No such nick");

    // (Optionnel : vérifier que client est opérateur, ou +i)

    std::string msg = ":" + client.getNickname() + " INVITE " +
                      nickname + " " + channelName;
    target->sendMessage(msg);
}
