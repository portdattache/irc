/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:51:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:21:49 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Topic.hpp"

Channel::Channel(const std::string &name) : _name(name), _mode(new Mode())
{
}

Channel::Channel(const Channel &copy)
{
	*this = copy;
}

Channel &Channel::operator=(const Channel &copy)
{
	if (this != &copy)
	{
		_name = copy._name;
		_members = copy._members;
	}
	return (*this);
}

Channel::~Channel()
{
	delete (_mode);
}

// GETTER //

const std::string &Channel::getName() const
{
	return (_name);
}

// MEMBERS PARAMS //

void Channel::addMember(Client *client)
{
	_members.push_back(client);
}

void Channel::removeMember(Client *client)
{
	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (*it == client)
		{
			_members.erase(it);
			break ;
		}
	}
}

void Channel::broadcast(const std::string &message)
{
	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
		(*it)->sendMessage(message);
}

Topic &Channel::getTopic()
{
	return (*_topic);
}

// void Channel::broadcastTopicChanged(const Client &client)
// {
// 	std::string msg = ":" + client.getNickname() + " TOPIC " + _name + " :"
// 		+ _topic.getTopic() + "\r\n";
// 	broadcast(msg);
// }

bool Channel::isOperator(const Client &client) const
{
	for (std::vector<Client *>::const_iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if ((*it)->getNickname() == client.getNickname())
			return (true);
	}
	return (false);
}

void Channel::addOperator(Client *client)
{
	if (!isOperator(*client))
		_operators.push_back(client);
}

void Channel::removeOperator(Client *client)
{
	for (std::vector<Client *>::iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if ((*it)->getNickname() == client->getNickname())
		{
			it = _operators.erase(it);
			return ;
		}
	}
}

Mode &Channel::getMode()
{
	return (*_mode);
}
