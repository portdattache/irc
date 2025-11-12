/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:48:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 13:15:29 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "CommandHandler.hpp"
#include "ICommand.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

CommandHandler::CommandHandler()
{
	registerCommand("JOIN", new JoinCmd());
	registerCommand("PRIVMSG", new PrivMsgCmd());
	registerCommand("KICK", new KickCmd());
	registerCommand("TOPIC", new TopicCmd());
	registerCommand("MODE", new ModeCmd());
	registerCommand("INVITE", new InviteCmd());
	registerCommand("NICK", new NickCmd());
	registerCommand("PING", new PingCmd());
	registerCommand("USER", new UserCmd());
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

void CommandHandler::registerCommand(const std::string &name, ICommand *cmd)
{
	if (!cmd)
		return ;
	_commands[name] = cmd;
}

void CommandHandler::handle(Server &server, Client &client,
	const std::string &cmd)
{
	if (cmd.empty())
		return ;
	std::istringstream ss(cmd);
	std::string cmdName;
	ss >> cmdName;
	// ======= Extraction des arguments ==================
	std::vector<std::string> args;
	std::string arg;
	while (ss >> arg)
		args.push_back(arg);
	std::map<std::string, ICommand *>::iterator it = _commands.find(cmdName);
	if (it != _commands.end())
		it->second->execute(server, client, args);
	else
		client.sendMessage(ERR_UNKNOWNCOMMAND);
}
