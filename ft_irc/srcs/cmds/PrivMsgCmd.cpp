/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCmd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:35:59 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 21:06:07 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivMsgCmd.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PrivMsgCmd::execute(Server &server, Client &client,
                         const std::vector<std::string> &args)
{
	if (!client.isRegistered())
    return sendError(server, client, ERR_NOTONCHANNEL, "PRIVMSG",
                     "You have not registered");
					 
	if (args.size() < 2)
    return sendError(server, client, ERR_NEEDMOREPARAMS, "PRIVMSG",
                     "Not enough parameters");


    std::string target = args[0];
    std::string message = args[1];
    if (!message.empty() && message[0] == ':')
        message = message.substr(1);

    if (!target.empty() && target[0] == '#')
    {
        Channel *chan = server.getChannel(target);
        if (!chan)
            return sendError(server, client, ERR_NOSUCHCHANNEL, target,
                    "No such channel");

        std::string msg = ":" + client.getNickname() + " PRIVMSG " +
                    target + " :" + message;
        chan->broadcast(msg);
    }
    else
    {
        Client *to = server.getClientByNick(target);
        if (!to)
            return sendError(server, client, ERR_NOSUCHNICK, target,
                        "No such nick");
        std::string msg = ":" + client.getNickname() + " PRIVMSG " +
                          target + " :" + message;
        to->sendMessage(msg);
    }
}
