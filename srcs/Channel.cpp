/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:51:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/28 22:07:29 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Topic.hpp"

Channel::Channel(const std::string &name) : _name(name), _mode(new Mode()),
	_topic(new Topic())
{
}

Channel::Channel(const Channel &copy)
{
	*this = copy;
}

Channel &Channel::operator=(const Channel &copy)
{
	delete	_mode;
	delete	_topic;

	if (this != &copy)
	{
		_name = copy._name;
		_members = copy._members;
		if (_mode)
			if (_topic)
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
	_members.insert(client);
}

void Channel::removeMember(Client *client)
{
    _members.erase(client);
    if (client)
        _operators.erase(client->getFd());
}


void Channel::broadcast(const std::string &message)
{
	for (std::set<Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
		(*it)->sendMessage(message);
}

Topic &Channel::getTopic()
{
	return (*_topic);
}

bool Channel::isOperator(const Client &client) const
{
    return (_operators.count(client.getFd()) > 0);
}

void Channel::addOperator(Client *client)
{
    _operators.insert(client->getFd());
}

void Channel::removeOperator(Client *client)
{
    _operators.erase(client->getFd());
}

bool Channel::isMember(const Client &client) const
{
	return (_members.count(const_cast<Client *>(&client)) > 0);
}

Mode &Channel::getMode()
{
	return (*_mode);
}

bool Channel::isInvited(const Client &client) const
{
	return (_invited.count(const_cast<Client *>(&client)) > 0);
}

void Channel::addInvitation(Client *client)
{
	_invited.insert(client);
}

void Channel::removeInvitation(Client *client)
{
	_invited.erase(client);
}

size_t Channel::getMemberCount() const
{
	return (_members.size());
}

const std::set<Client *> &Channel::getMembers() const
{
	return (_members);
}
