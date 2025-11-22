/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:33:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 15:32:27 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class	Mode;
class	Client;
class	Topic;

class Channel
{
  private:
	std::string _name;
	std::string _key;
	std::vector<Client *> _members;
	std::vector<Client *> _operators;
	Mode *_mode;
	Topic *_topic;

  public:
	Channel(const std::string &name);
	Channel(const Channel &copy);
	Channel &operator=(const Channel &copy);
	~Channel();

	// CHANNEL PUBLIC METHODS //
	const std::string &getName() const;
	void addMember(Client *client);
	void removeMember(Client *client);
	void addOperator(Client *client);
	void removeOperator(Client *client);
	void broadcast(const std::string &message);
	void broadcastTopicChanged(const Client &client);
	Topic &getTopic();
	bool isOperator(const Client &client) const;
	bool isMember(const Client &client) const;
	Mode &getMode();
};

#endif
