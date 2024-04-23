
#include "../HEADERS/server.hpp"



void server::ft_part(std::vector<std::string> Cmds, client & Client, int Socket)
{
    if(ft_is_registred(Client, Socket) == false)
        return ;
    if(Cmds.size() == 1)
    {
        std::string msg = Client.getNickname() + " PART (411) :No recipient given";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    if(ft_find_a_channel(Cmds[1]) == false)
    {
        std::string msg = Client.getNickname() + " PART (403) :No such channel";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    channel & Channel = ft_get_channel(Cmds[1]);
    if(Channel.isMember(Client.getNickname()) == false)
    {
        std::string msg = Client.getNickname() + " PART (442) :You're not on that channel";
        ft_send(Socket, msg.c_str(), msg.size(), 0);
        return ;
    }
    Channel.removeMember(Client.getNickname());
    std::string msg = ":" + Client.getNickname() + " PART " + Channel.getName();
    std::vector<client > Members = Channel.getMembers();
    for(size_t i = 0; i < Members.size(); i++)
    {
        if(Members[i].getNickname() != Client.getNickname())
            ft_send(Members[i].getSocket(), msg.c_str(), msg.size(), 0);
    }
}