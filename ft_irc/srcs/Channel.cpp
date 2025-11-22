/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:51:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 15:37:51 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Topic.hpp"

Channel::Channel(const std::string &name) : 
	_name(name), 
	_mode(new Mode()),
	_topic(new Topic())
{}

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
		if (_mode) delete _mode;
		if (_topic) delete _topic;
		_mode = new Mode(*copy._mode);
		_topic = new Topic(*copy._topic);
	}
	return (*this);
}

Channel::~Channel()
{
	delete (_mode);
	delete (_topic);
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
bool Channel::isMember(const Client &client) const
{
	for (size_t i = 0; i < _members.size(); i++)
	{
		if (_members[i] == &client)
			return true;
	}
	return false;
}

Mode &Channel::getMode()
{
	return (*_mode);
}
