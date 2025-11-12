/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:48:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:45:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"
#include "ICommand.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

CommandHandler::CommandHandler()
{
	_commands["JOIN"] = new JoinCmd();
	_commands["PRIVMSG"] = new PrivMsgCmd();
	_commands["KICK"] = new KickCmd();
	_commands["TOPIC"] = new TopicCmd();
	_commands["MODE"] = new ModeCmd();
	_commands["INVITE"] = new InviteCmd();
}

CommandHandler::CommandHandler(const CommandHandler &copy)
{
	(void)copy;
}

CommandHandler &CommandHandler::operator=(const CommandHandler &copy)
{
	(void)copy;
	return (*this);
}

CommandHandler::~CommandHandler()
{
	for (std::map<std::string,
		ICommand *>::iterator it = _commands.begin(); it != _commands.end(); ++it)
		delete (it->second);
}

void CommandHandler::handle(Server &server, Client &client,
	const std::string &cmdName, const std::vector<std::string> &args)
{
	std::map<std::string, ICommand *>::iterator it = _commands.find(cmdName);
	if (it == _commands.end())
		return (sendError(client, ERR_UNKNOWNCOMMAND));
	it->second->execute(server, client, args);
}
