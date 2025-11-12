/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:37:21 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:46:54 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECMD_HPP
# define INVITECMD_HPP

# include "ICommand.hpp"

class InviteCmd : public ICommand
{
	virtual void execute(Server &server, Client &client,
		const std::vector<std::string> &args);
};

#endif