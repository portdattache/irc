/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapCmd.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:38:44 by broboeuf          #+#    #+#             */
/*   Updated: 2025/11/20 16:42:22 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CapCmd.hpp"
#include "Client.hpp"

void CapCmd::execute(Server &server, Client &client, 
                const std::vector<std::string> &args)
{
    (void)server;
    (void)args;
    client.sendMessage("CAP * ACK :\r\n");
}