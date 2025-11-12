/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:41:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 21:42:08 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void UserCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	(void)server;
	if (args.size() < 2)
		return (client.sendMessage(ERR_NEEDMOREPARAMS));
	client.setUsername(args[0]);
	server.tryRegister(client);
}
