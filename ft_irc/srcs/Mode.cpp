/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:33:19 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:58:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Mode.hpp"

Mode::Mode() : _inviteOnly(false), _topicLocked(false), _hasKey(false),
	_hasLimit(false), _limit(0), _key("")
{
}

Mode::Mode(const Mode &copy)
{
	(void)copy;
}

Mode &Mode::operator=(const Mode &copy)
{
	(void)copy;
	return (*this);
}

Mode::~Mode()
{
}

bool Mode::isInviteOnly() const
{
	return (_inviteOnly);
}

bool Mode::isTopicLocked() const
{
	return (_topicLocked);
}

bool Mode::checkKey(const std::string &key) const
{
	return (_hasKey && _key == key);
}

bool Mode::hasLimit() const
{
	return (_hasLimit);
}

size_t Mode::getLimit() const
{
	return (_limit);
}

void Mode::setInvinteOnly(bool mode)
{
	_inviteOnly = mode;
}

void Mode::setTopicLocked(bool mode)
{
	_topicLocked = mode;
}

void Mode::setKey(const std::string &key)
{
	_hasKey = true;
	_key = key;
}

void Mode::setLimit(size_t limit)
{
	_hasLimit = true;
	_limit = limit;
}

void Mode::clearKey()
{
	_hasKey = false;
	_key.clear();
}

void Mode::clearLimit()
{
	_hasLimit = false;
	_limit = 0;
}

// void Mode::apply(const std::string &flags, Client *client)
// {
// 	bool	adding;
// 	char	c;
// 	size_t	nextSpace;

// 	adding = true;
// 	for (size_t i = 0; i < flags.size(); ++i)
// 	{
// 		c = flags[i];
// 		if (c == '+')
// 		{
// 			adding = true;
// 			continue ;
// 		}
// 		if (c == '-')
// 		{
// 			adding = false;
// 			continue ;
// 		}
// 		switch (c)
// 		{
// 		case 'i':
// 			setInvinteOnly(adding);
// 			break ;
// 		case 't':
// 			setTopicLocked(adding);
// 			break ;
// 		case 'k':
// 		{
// 			nextSpace = flags.find(' ', i + 1);
// 			std::string key;
// 			if (nextSpace != std::string::npos)
// 				key = flags.substr(i + 1, nextSpace - i - 1);
// 			else
// 				key = flags.substr(i + 1);
// 			if (adding)
// 				setKey(key);
// 			else
// 				setKey("");
// 			i += key.size();
// 			break ;
// 		}
// 		case 'l':
// 		{
// 			std::string limitStr;
// 			nextSpace = flags.find(' ', i + 1);
// 			if (nextSpace != std::string::npos)
// 				limitStr = flags.substr(i + 1, nextSpace - i - 1);
// 			else
// 				limitStr = flags.substr(i + 1);
// 			if (adding)
// 				setLimit(atoi(limitStr.c_str()));
// 			else
// 				setLimit(0);
// 			i += limitStr.size();
// 			break ;
// 		}
// 		case 'o':
// 		{
// 			break ;
// 		}
// 		default:
// 			if (client)
// 				client->sendMessage(ERR_UNKNOWNMODE);
// 		}
// 	}
// }

std::string Mode::getModeString() const
{
	std::string result;
	if (_inviteOnly)
		result += "i";
	if (_topicLocked)
		result += "t";
	if (_hasKey)
		result += "k";
	if (_hasLimit)
		result += "l";
	return (result);
}
