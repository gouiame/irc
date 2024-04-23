/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouiame <cgouiame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:17:43 by hed-dyb           #+#    #+#             */
/*   Updated: 2024/04/18 21:50:28 by cgouiame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client.hpp"
#include <iostream>
#include <vector>

class client;

class channel
{
	private :
		std::string Name;
		std::string Topic;
		std::string Password;
		size_t		Limit;

		bool PassWordStatus;
		bool InvitaionStatus;
		bool TopicStatus;
		bool AdminStatus;
		bool LimitStatus;		//l: Set/remove the user limit to channel

		std::vector<client > Members;
		std::vector<client > Admins;
		std::vector<client > Invited;
		
		time_t TopicTime;
			
	public :
		channel();
		void ft_channel_init();
		
		// Getters / Setters ------------------
		void setName(std::string Name);
		void setTopic(std::string Topic);
		void setPassword(std::string Password);
		void setLimit(size_t Limit);
		
		void setInvitaionStatus(bool Status);
		void setTopicStatus(bool Status);
		void setPassWordStatus(bool Status);
		void setAdminStatus(bool Status);
		void setLimitStatus(bool Status);
		
		std::string getName();
		std::string getTopic();
		std::string getPassword();
		size_t		getLimit();
		
		bool getInvitaionStatus();
		bool getTopicStatus();
		bool getPassWordStatus();
		bool getAdminStatus();
		bool getLimitStatus();
		

		// utilts -----------------
		
		void ft_add_member(client & Client);
		void ft_add_admin(client & Client);
		void ft_add_invited(client & Client);
		
		std::vector<client > getMembers();
		std::vector<client > getAdmins();
		std::vector<client > getInvited();

		
		bool ft_find_client(std::string list, std::string Nickname);// list == Members, admins, ...ext  return -1 if do no exist , return indice of it if it exist 
		
		std::string ft_list_admins_and_members();
		bool ft_a_member_or_admin(std::string Nick);
		size_t ft_channel_size();
		// added by shaimaa
		void ft_save_topicTime();
		std::string getTopicTime();
		
		
};