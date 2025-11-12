/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:28:29 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:14:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class	Channel;

class Client
{
  private:
	int _fd;
	bool _registered;
	std::string _nickname;
	std::string _username;
	std::string _buffer;

  public:
	Client(int fd);
	Client(const Client &copy);
	Client &operator=(const Client &copy);
	~Client();

	// Public Client Methods //
	int getFd() const;
	bool isRegistered() const;
	void setNickname(const std::string &nick);
	void setUsername(const std::string &user);
	void setRegistered(bool state);
	void addToBuffer(const std::string &data);
	void sendMessage(const std::string &msg);
	const std::string &getNickname() const;
	const std::string &getUsername() const;
	std::string extractCommand();
	std::string toString() const;
	bool hasNickname() const;
	void Registered();
};

#endif