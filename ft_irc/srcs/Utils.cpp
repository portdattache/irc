/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:31:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 21:28:39 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void sendError(Server &server, Client &client, const std::string &code,
			   const std::string &params, const std::string &text)
{
	client.sendMessage(":" + server.getName() + " " + code + " " +
					   client.getNickname() + (params.empty() ? "" : " " + params) +
					   (text.empty() ? "" : " :" + text));
}

void sendReply(Server &server, Client &client, const std::string &code,
			   const std::string &params, const std::string &text)
{
	client.sendMessage(":" + server.getName() + " " + code + " " +
					   client.getNickname() + (params.empty() ? "" : " " + params) +
					   (text.empty() ? "" : " :" + text));
}