/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:33:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/28 22:07:43 by bcaumont         ###   ########.fr       */
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
	std::set<Client *> _members;
	std::set<int> _operators;
	std::set<Client *> _invited;
	Mode *_mode;
	Topic *_topic;

  public:
	Channel(const std::string &name);
	Channel(const Channel &copy);
	Channel &operator=(const Channel &copy);
	~Channel();

	// CHANNEL PUBLIC METHODS //
	const std::string &getName() const;
	const std::set<Client *> &getMembers() const;
	void addMember(Client *client);
	void removeMember(Client *client);
	void addOperator(Client *client);
	void removeOperator(Client *client);
	void broadcast(const std::string &message);
	bool isOperator(const Client &client) const;
	bool isMember(const Client &client) const;
	bool isInvited(const Client &client) const;
	void addInvitation(Client *client);
	void removeInvitation(Client *client);
	size_t getMemberCount() const;
	Topic &getTopic();
	Mode &getMode();
};

#endif
