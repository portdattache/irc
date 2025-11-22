/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:48:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 21:25:52 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHandler.hpp"
#include "PassCmd.hpp"
#include "NickCmd.hpp"
#include "UserCmd.hpp"
#include "PingCmd.hpp"
#include "JoinCmd.hpp"
#include "PartCmd.hpp"
#include "PrivMsgCmd.hpp"
#include "KickCmd.hpp"
#include "InviteCmd.hpp"
#include "ModeCmd.hpp"
#include "TopicCmd.hpp"
#include "QuitCmd.hpp"
#include "CapCmd.hpp"

#include "Client.hpp"
#include "Server.hpp"

CommandHandler::CommandHandler()
{
    registerCommand("PASS", new PassCmd());
    registerCommand("NICK", new NickCmd());
    registerCommand("USER", new UserCmd());
    registerCommand("PING", new PingCmd());
    registerCommand("JOIN", new JoinCmd());
    registerCommand("PRIVMSG", new PrivMsgCmd());
    registerCommand("KICK", new KickCmd());
    registerCommand("INVITE", new InviteCmd());
    registerCommand("MODE", new ModeCmd());
    registerCommand("TOPIC", new TopicCmd());
    registerCommand("PART", new PartCmd());
    registerCommand("QUIT", new QuitCmd());
    registerCommand("CAP", new CapCmd());
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
