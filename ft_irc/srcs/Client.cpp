/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:30:18 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/21 10:41:36 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Channel.hpp"
#include "ft_irc.hpp"

Client::Client(int fd) : 
	_fd(fd), 
	_registered(false),
	_passOk(false)
{}

Client::Client(const Client &copy)
{
	*this = copy;
}

Client &Client::operator=(const Client &copy)
{
	if (this != &copy)
	{
		_nickname = copy._nickname;
		_username = copy._username;
		_buffer = copy._buffer;
		_fd = copy._fd;
		_registered = copy._registered;
	}
	return (*this);
}

Client::~Client()
{
	close(_fd);
}

// GETTERS //

int Client::getFd() const
{
	return (_fd);
}

const std::string &Client::getNickname() const
{
	return (_nickname);
}

const std::string &Client::getUsername() const
{
	return (_username);
}

bool Client::isRegistered() const
{
	return (_registered);
}

// SETTERS //

void Client::setNickname(const std::string &nick)
{
	_nickname = nick;
}

void Client::setUsername(const std::string &user)
{
	_username = user;
}

void Client::setRegistered(bool state)
{
	_registered = state;
}

void Client::addToBuffer(const std::string &data)
{
	_buffer += data;
}

bool Client::hasNickname() const
{
	return (!_nickname.empty());
}

void Client::Registered()
{
	_registered = true;
}

bool Client::isPassOk() const
{
	return (_passOk);
}

void Client::setPassOk(bool v)
{
	_passOk = v;
}

std::string Client::toString() const
{
	return (_nickname + " (" + _username + ")");
}

// EXTRACTOR //

std::string Client::extractCommand()
{
	size_t	pos;

	pos = _buffer.find("\r\n");
	std::string cmd;
	if (pos == std::string::npos)
		return ("");
	cmd = _buffer.substr(0, pos);
	_buffer.erase(0, pos + 2);
	return (cmd);
}

void Client::sendMessage(const std::string &msg)
{
	std::string formatted = msg + "\r\n";
	send(_fd, formatted.c_str(), formatted.size(), MSG_NOSIGNAL);
}
