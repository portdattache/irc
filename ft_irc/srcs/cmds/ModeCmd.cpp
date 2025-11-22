/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:41:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 20:51:17 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCmd.hpp"
#include "Utils.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void ModeCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	if (!client.isRegistered())
		return sendError(server, client, ERR_NOTONCHANNEL, "MODE",
				"You have not registered");
	if (args.empty())
		return sendError(server, client, ERR_NEEDMOREPARAMS, "MODE",
				"Not enough parameters");
	
	std::string channelName = args[0];
	Channel *chan = server.getChannel(channelName);
	if (!chan)
			return sendError(server, client, ERR_NOSUCHCHANNEL, channelName,
					"No such channel");

	if (args.size() == 1)
	{
		std::string modeStr = chan->getMode().getModeString();
		std::string params = channelName + " +" + modeStr;
		return sendReply(server, client, RPL_CHANNELMODEIS, params, "");
	}
	if (!chan->isOperator(client))
		return sendError(server, client, ERR_CHANOPRIVSNEEDED, channelName,
				"You're not channel operator");
	
	std::string modeFlags = args[1];
	size_t argIndex = 2;
	bool adding = true;
	char flag;
	Client *target;

	for (size_t i = 0; i < modeFlags.size(); i++)
	{
		flag = modeFlags[i];
		if (flag == '+')
		{
			adding = true;
			continue;
		}
		if (flag == '-')
		{
			adding = false;
			continue;
		}
		switch (flag)
		{
			case 'i':
				chan->getMode().setInvinteOnly(adding);
				break;
			case 't':
				chan->getMode().setTopicLocked(adding);
				break;
			case 'k':
				if (adding)
				{
					if (argIndex >= args.size())
						return sendError(server, client, ERR_NEEDMOREPARAMS,
								"MODE", "Not enough parameters");
                    chan->getMode().setKey(args[argIndex++]);
                }
                else
                    chan->getMode().clearKey();
                break;
            case 'l':
                if (adding)
                {
                    if (argIndex >= args.size())
                        return sendError(server, client, ERR_NEEDMOREPARAMS,
                                         "MODE", "Not enough parameters");
                    chan->getMode().setLimit(
                        static_cast<size_t>(atoi(args[argIndex++].c_str())));
                }
                else
                    chan->getMode().clearLimit();
                break;
            case 'o':
                if (argIndex >= args.size())
                    return sendError(server, client, ERR_NEEDMOREPARAMS,
                                     "MODE", "Not enough parameters");
                target = server.getClientByNick(args[argIndex++]);
                if (!target)
                    return sendError(server, client, ERR_NOSUCHNICK,
                                     args[argIndex - 1], "No such nick");
                if (adding)
                    chan->addOperator(target);
                else
                    chan->removeOperator(target);
                break;
            default:
                sendError(server, client, ERR_UNKNOWNMODE,
                          std::string(1, flag), "Unknown mode");
                break;
        }
    }

    std::string msg = ":" + client.getNickname() + " MODE " +
                      channelName + " " + args[1];
    chan->broadcast(msg);
}
