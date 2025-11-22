/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:36:51 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 20:52:54 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCmd.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void JoinCmd::execute(Server &server, Client &client,
                      const std::vector<std::string> &args)
{
    if (!client.isRegistered())
        return sendError(server, client, ERR_NOTONCHANNEL, "JOIN",
                         "You have not registered");

    if (args.empty())
        return sendError(server, client, ERR_NEEDMOREPARAMS, "JOIN",
                         "Not enough parameters");

    std::string chanName = args[0];

    Channel *chan = server.getChannel(chanName);
    if (!chan)
        chan = server.createChannel(chanName);

    chan->addMember(&client);

    std::string joinMsg = ":" + client.getNickname() + " JOIN " + chanName;
    chan->broadcast(joinMsg);
}
