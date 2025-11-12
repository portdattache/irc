/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:37:53 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 21:25:44 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PingCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	const std::string token = args.empty() ? server.getName() : args[0];
	client.sendMessage(":" + server.getName() + " PONG " + server.getName() + " :" + token);
}
