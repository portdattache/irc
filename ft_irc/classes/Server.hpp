/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:19:01 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:16:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

class	Channel;
class	Client;

class Server
{
  private:
	int _port;
	int _socket_fd;
	std::string _name;
	std::string _password;
	std::vector<struct pollfd> _pollfds;
	std::map<int, Client *> _clients;
	std::map<std::string, Channel *> _channels;
	std::map<std::string, ICommand *> cmd;

	// Server private methods //
	void acceptNewClient();
	void removeClient(int fd);
	void handleClientMessage(int fd);
	void handleCommand(Client *client, const std::string &cmd);

  public:
	Server(int port, const std::string &password);
	Server(const Server &copy);
	Server &operator=(const Server &copy);
	~Server();

	// Server public methods //
	void run();
	void registerCommands();
	std::string getName() const;
	Client *getClientByNick(const std::string &nickname);
	Channel *getChannel(const std::string &name);
	Channel *createChannel(const std::string &name);
};

#endif
