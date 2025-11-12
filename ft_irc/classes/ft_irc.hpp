/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:38:15 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:13:54 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

// ========== CODE ERROR DEFINES ===========

# define ERR_NOSUCHNICK "401"        // No such nick/channel
# define ERR_NOSUCHCHANNEL "403"     // No such channel
# define ERR_CANNOTSENDTOCHAN "404"  // Cannot send to channel
# define ERR_UNKNOWNCOMMAND "421"    // Unknown command
# define ERR_UNKNOWNMODE "477"       // Unknown mode
# define ERR_NONICKNAMEGIVEN "431"   // No nickname given
# define ERR_ERRONEUSNICKNAME "432"  // Erroneous nickname
# define ERR_NICKNAMEINUSE "433"     // Nickname in use
# define ERR_USERNOTINCHANNEL "441"  // User not in channel
# define ERR_NOTONCHANNEL "442"      // You're not on that channel
# define ERR_USERONCHANNEL "443"     // User already on channel
# define ERR_NEEDMOREPARAMS "461"    // Not enough parameters
# define ERR_ALREADYREGISTERED "462" // Already registered
# define ERR_PASSWDMISMATCH "464"    // Password incorrect
# define ERR_CHANOPRIVSNEEDED "482"  // Channel operator privileges needed
# define ERR_INVITEONLYCHAN "473"    // Cannot join invite-only channel
# define ERR_CHANNELISFULL "471"     // Channel is full
# define ERR_KEYSET "467"            // Channel key already set

// ========== REPLIES CODE DEFINES =========

# define RPL_WELCOME "001"
# define RPL_YOURHOST "002"
# define RPL_CREATED "003"
# define RPL_MYINFO "004"
# define RPL_NOTOPIC "331"
# define RPL_TOPIC "332"
# define RPL_NAMREPLY "353"
# define RPL_ENDOFNAMES "366"
# define RPL_INVITING "341"
# define RPL_ENDOFWHO "315"

// ========== LIBRAIRIES STANDARD ==========
# include <algorithm>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <map>
# include <set>
# include <sstream>
# include <stdexcept>
# include <string>
# include <vector>

// ========== LIBRAIRIES RÉSEAU ==========
# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <fcntl.h>
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

// ========== Interface ===================

class	ICommand;

// ========== INCLUDES DU PROJET ==========
// # include "Channel.hpp" //Gestion des channels
// # include "Client.hpp" // Gestion du ou des clients
// # include "CommandHandler.hpp" // Routeur des commandes
// # include "ICommand.hpp" // Interface des commandes
// # include "Mode.hpp" // Gestion des modes
// # include "Server.hpp" // Gestion du server
// # include "Topic.hpp" // Gestion des topics
// # include "Utils.hpp" // Error replies &  Utils

// ========== INCLUDES DES COMMANDES ======
# include "cmds/InviteCmd.hpp"
# include "cmds/JoinCmd.hpp"
# include "cmds/KickCmd.hpp"
# include "cmds/ModeCmd.hpp"
# include "cmds/NickCmd.hpp"
# include "cmds/PingCmd.hpp"
# include "cmds/PrivMsgCmd.hpp"
# include "cmds/TopicCmd.hpp"
# include "cmds/UserCmd.hpp"

#endif