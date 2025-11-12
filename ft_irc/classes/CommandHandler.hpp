/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:29:42 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:33:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDHANDLER_HPP
# define COMMANDHANDLER_HPP

# include "ft_irc.hpp"

class	Server;
class	Client;
class	ICommand;

class CommandHandler
{
  private:
	std::map<std::string, ICommand *> _commands;

  public:
	CommandHandler();
	CommandHandler(const CommandHandler &copy);
	CommandHandler &operator=(const CommandHandler &copy);
	~CommandHandler();
	void handle(Server &server, Client &client, const std::string &cmdName,
		const std::vector<std::string> &args);
	void registerCommand(const std::string &name, ICommand *cmd);
};

#endif