#include "../HEADERS/server.hpp"

void ft_channel_member(std::string Channel, std::string Nickname)
{
    for(size_t i = 0; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel)
        {
            for(size_t j = 0; j < Channels[i].getMembers().size(); j++)
            {
                if(Channels[i].getMembers()[j] == Nickname)
                    return true;
            }
            return false;
        }
    }
    return false;
}

void ft_remove_channel_member(std::string Channel, std::string Nickname)
{
    for(size_t i = 0; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel)
        {
            for(size_t j = 0; j < Channels[i].getMembers().size(); j++)
            {
                if(Channels[i].getMembers()[j] == Nickname)
                {
                    Channels[i].getMembers().erase(Channels[i].getMembers().begin() + j);
                    return ;
                }
            }
        }
    }
}

void ft_send_to_channel(std::string Channel, std::string msg)
{
    for(size_t i = 0; i < Channels.size(); i++)
    {
        if(Channels[i].getName() == Channel)
        {
            for(size_t j = 0; j < Channels[i].getMembers().size(); j++)
            {
                for(size_t k = 0; k < Clients.size(); k++)
                {
                    if(Clients[k].getNickname() == Channels[i].getMembers()[j])
                    {
                        ft_send(Clients[k].getSocket(), msg.c_str(), msg.size(), 0);
                        break ;
                    }
                }
            }
        }
    }
}

void server::ft_part(std::vector<std::string> & Cmds, client & Client, int Socket)
{
    if(ft_is_registred(Client, Socket) == false)
        return ;
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " (461) :Not enough parameters";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    std::vector<std::string> Channels = ft_split_with_comma(Cmds[1]);
    for(size_t i = 0; i < Channels.size(); i++)
    {
        if(ft_channel_exist(Channels[i]) == false)
        {
            std::string msg = Client.getNickname() + " (403) " + Channels[i] + " :No such channel";
            ft_send(Socket, msg.c_str(), msg.size(), 0);
            continue ;
        }
        if(ft_channel_member(Channels[i], Client.getNickname()) == false)
        {
            std::string msg = Client.getNickname() + " (442) " + Channels[i] + " :You're not on that channel";
            ft_send(Socket, msg.c_str(), msg.size(), 0);
            continue ;
        }
        ft_remove_channel_member(Channels[i], Client.getNickname());
        std::string msg = ":" + Client.getNickname() + " PART " + Channels[i] + "\r\n";
        ft_send_to_channel(Channels[i], msg);
    }
}