/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:20:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:19:21 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

Server::Server(int port, const std::string &password) : _port(port),
	_socket_fd(-1), _password(password)
{
}

Server::Server(const Server &copy)
{
	*this = copy;
}

Server &Server::operator=(const Server &copy)
{
	if (this != &copy)
	{
		_channels = copy._channels;
		_clients = copy._clients;
		_pollfds = copy._pollfds;
		_port = copy._port;
		_socket_fd = copy._socket_fd;
		_password = copy._password;
	}
	return (*this);
}

Server::~Server()
{
	if (_socket_fd != -1)
		close(_socket_fd);
	for (std::map<int,
		Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		delete (it->second);
	for (std::map<std::string,
		Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		delete (it->second);
}

void Server::run()
{
	struct sockaddr_in	addr;
	int					opt;
	struct pollfd		serverPoll;

	opt = 1;
	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_fd < 0)
		throw std::runtime_error("Socket creation failed.");
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Setsockopt failed");
	fcntl(_socket_fd, F_SETFL, O_NONBLOCK);
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(_port);
	if (bind(_socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error("Bind failed");
	if (listen(_socket_fd, 10) < 0)
		throw std::runtime_error("Listen failed");
	std::cout << "Server running on port: " << _port << std::endl;
	serverPoll.fd = _socket_fd;
	serverPoll.events = POLLIN;
	_pollfds.push_back(serverPoll);
	while (1)
	{
		if (poll(&_pollfds[0], _pollfds.size(), -1) < 0)
			throw std::runtime_error("Poll failed");
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents & POLLIN)
			{
				if (_pollfds[i].fd == _socket_fd)
					acceptNewClient();
				else
					handleClientMessage(_pollfds[i].fd);
			}
		}
	}
}

void Server::acceptNewClient()
{
	struct sockaddr_in	clientAddr;
	socklen_t			clientLen;
	int					clientFd;
	struct pollfd		clientPoll;
	Client				*newClient;

	clientLen = sizeof(clientAddr);
	clientFd = accept(_socket_fd, (struct sockaddr *)&clientAddr, &clientLen);
	if (clientFd < 0)
		return ;
	fcntl(clientFd, F_SETFL, O_NONBLOCK);
	clientPoll.fd = clientFd;
	clientPoll.events = POLLIN;
	_pollfds.push_back(clientPoll);
	std::map<int, Client *> clients;
	newClient = new Client(clientFd);
	_clients.insert(std::make_pair(clientFd, newClient));
	std::cout << "New client connected: " << clientFd << std::endl;
}

// void Server::handleClientMessage(int clientFd)
// {
// 	char	buf[512];
// 	ssize_t	bytes;

// 	bytes = recv(clientFd, buf, sizeof(buf) - 1, 0);
// 	if (bytes <= 0)
// 	{
// 		std::cout << "Client disconnected: " << clientFd << std::endl;
// 		close(clientFd);
// 		for (std::vector<pollfd>::iterator it = _pollfds.begin(); it != _pollfds.end(); ++it)
// 		{
// 			if (it->fd == clientFd)
// 			{
// 				_pollfds.erase(it);
// 				break ;
// 			}
// 		}
// 		_clients.erase(clientFd);
// 		return ;
// 	}
// 	buf[bytes] = '\0';
// 	_clients[clientFd]->addToBuffer(buf);
// 	std::string message;
// 	while (!(message = _clients[clientFd]->extractCommand()).empty())
// 		CommandHandler::handleCommand(*this, *(_clients[clientFd]), message);
// }

Client *Server::getClientByNick(const std::string &nickname)
{
	for (std::map<int,
		Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second->getNickname() == nickname)
			return (it->second);
	}
	return (NULL);
}

std::string Server::getName() const
{
	return (_name);
}

Channel *Server::getChannel(const std::string &name)
{
	std::map<std::string, Channel *>::iterator it = _channels.find(name);
	if (it != _channels.end())
		return (it->second);
	return (NULL);
}

Channel *Server::createChannel(const std::string &name)
{
	Channel	*newChannel;

	newChannel = new Channel(name);
	_channels[name] = newChannel;
	return (newChannel);
}
