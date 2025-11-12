/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:41:11 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:22:23 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Topic.hpp"
#include "ft_irc.hpp"

Topic::Topic() : _topic(""), _author(""), _timestamp(0)
{
}

Topic::Topic(const Topic &copy)
{
	(void)copy;
}

Topic &Topic::operator=(const Topic &copy)
{
	(void)copy;
	return (*this);
}

Topic::~Topic()
{
}

const std::string &Topic::getTopic() const
{
	return (_topic);
}

const std::string &Topic::getAuthor() const
{
	return (_author);
}

time_t Topic::getTimestamp() const
{
	return (_timestamp);
}

void Topic::setTopic(const std::string &topic, const std::string &author)
{
	_topic = topic;
	_author = author;
	_timestamp = std::time(NULL);
}

void Topic::clear()
{
	_topic = "";
	_author = "";
	_timestamp = 0;
}
