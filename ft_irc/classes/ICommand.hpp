/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:51:25 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:31:40 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include "ft_irc.hpp"

class	Server;
class	Client;

class ICommand
{
  public:
	virtual void execute(Server &server, Client &client,
			const std::vector<std::string> &args) = 0;
	virtual ~ICommand()
	{
	}
};

#endif