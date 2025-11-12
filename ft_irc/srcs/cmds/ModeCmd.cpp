/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:41:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 18:38:12 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void ModeCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	bool	adding;
	char	flag;
	Client	*target;
	size_t	argIndex;

	if (args.empty())
		return (client.sendMessage(ERR_NEEDMOREPARAMS));
	std::string channelName = args[0];
	chan = server.getChannel(channelName);
	if (!chan)
		return (client.sendMessage(ERR_NOSUCHCHANNEL));
	if (args.size() == 1)
	{
		std::string modeStr = chan->getMode().getModeString();
		return (client.sendMessage(":" + client.getNickname() + " 324 "
				+ client.getNickname() + " " + channelName + " +" + modeStr));
	}
	if (!chan->isOperator(client))
		return (client.sendMessage(ERR_CHANOPRIVSNEEDED));
	std::string modeFlags = args[1];
	argIndex = 2;
	adding = true;
	for (size_t i = 0; i < modeFlags.size(); ++i)
	{
		flag = modeFlags[i];
		if (flag == '+')
		{
			adding = true;
			continue ;
		}
		if (flag == '-')
		{
			adding = false;
			continue ;
		}
		switch (flag)
		{
		case 'i':
			chan->getMode().setInvinteOnly(adding);
			break ;
		case 't':
			chan->getMode().setTopicLocked(adding);
			break ;
		case 'k':
			if (adding)
			{
				if (argIndex >= args.size())
					return (client.sendMessage(ERR_NEEDMOREPARAMS));
				chan->getMode().setKey(args[argIndex++]);
			}
			else
				chan->getMode().clearKey();
			break ;
		case 'l':
			if (adding)
			{
				if (argIndex >= args.size())
					return (client.sendMessage(ERR_NEEDMOREPARAMS));
				chan->getMode().setLimit(atoi(args[argIndex++].c_str()));
			}
			else
				chan->getMode().clearLimit();
			break;
		case 'o':
		{
			if (argIndex >= args.size())
				return (client.sendMessage(ERR_NEEDMOREPARAMS));
			target = server.getClientByNick(args[argIndex++]);
			if (!target)
				return (client.sendMessage(ERR_NOSUCHNICK));
			if (adding)
				chan->addOperator(target);
			else
				chan->removeOperator(target);
			break ;
		}
		default:
			client.sendMessage(ERR_UNKNOWNMODE);
			break ;
		}
	}
	chan->broadcast(":" + client.getNickname() + " MODE " + channelName + " "
		+ args[1]);
}
