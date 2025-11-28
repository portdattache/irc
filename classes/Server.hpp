/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:19:01 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 18:49:22 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Channel.hpp"
# include "Client.hpp"
# include "CommandHandler.hpp"
# include "ft_irc.hpp"

class	Channel;
class	Client;

class Server
{
  private:
	int _port;
	std::string _password;
	int _serverFd;
	std::string _name;
	std::map<int, Client *> _clients;
	std::map<std::string, Channel *> _channels;
	CommandHandler _cmdHandler;

  public:
	Server(int port, const std::string &password);
	Server(const Server &copy);
	Server &operator=(const Server &copy);
	~Server();

	// Server public methods //

	// === SERVER LAUNCHER === //
	void run();

	// === CLIENT GESTION ==== //
	void addClient(int fd);
	void removeClient(int fd);
	std::string getName() const;
	Client *getClientByNick(const std::string &nickname);

	// === CHANNEL GESTION ==== //
	Channel *getChannel(const std::string &name);
	Channel *createChannel(const std::string &name);
	const std::map<std::string, Channel*>& getChannels() const;

	// === MESSAGES GESTION === //
	void handleClientMessage(int clientFd, const std::string &message);
	void tryRegister(Client &client);
	int getServerFd() const;
	const std::string &getPassword() const;
};

#endif

