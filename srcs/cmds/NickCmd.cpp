/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:22:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 21:02:08 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCmd.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Utils.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void NickCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	if (args.empty())
		return sendError(server, client, ERR_NONICKNAMEGIVEN, "NICK",
				"No nickname given");
	std::string newNick = args[0];
	if (server.getClientByNick(newNick))
		return sendError(server, client,ERR_NICKNAMEINUSE, newNick, 
				"Nick is already in use");
	client.setNickname(newNick);
	server.tryRegister(client);
}
