/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:54:35 by broboeuf          #+#    #+#             */
/*   Updated: 2025/11/20 15:38:34 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartCmd.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PartCmd::execute(Server &server, Client &client,
                    const std::vector<std::string> &args)
{
    if (!client.isRegistered())
        return sendError(server, client, ERR_NOTREGISTERED , "PART",  "");
    if (args.empty())
        return sendError(server, client, ERR_NEEDMOREPARAMS, "PART", "");

    const std::string channelName = args[0];

    Channel *chan = server.getChannel(channelName);
    if (!chan)
        return sendError(server, client, ERR_NOSUCHCHANNEL, channelName, "");
    if (!chan->isMember(client.getFd()))
        return sendError(server, client, ERR_NOTONCHANNEL, channelName, "");

    std::string msg = ":" + client.getNickname() + "!" + 
        client.getUsername() + "@localhost PART" + channelName + "\r\n";
    
    chan->broadcast(msg);
    chan->removeMember(&client);
}

