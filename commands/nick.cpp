#include "command.hpp"

void nick(User &user, string newNickName, int fd){

    string nickName = user.getNickName(fd);
    string loginName = user.getLoginName(fd);
    string hostName = user.getHostName(fd);
    string fullMessage = prefixMessage(nickName, loginName, hostName, "NICK", newNickName);

    if (newNickName == ""){
        user.setWriteBuffer(fd, serverMessage(ERR_NONICKNAMEGIVEN, nickName, "", "", "No nickname given"));
        return;
    }
    if (validNickName(newNickName) == false)
    {
        user.setWriteBuffer(fd, serverMessage(ERR_ERRONEUSNICKNAME, nickName, newNickName, "", "Erroneous nickname"));
        return;
    }
    if(user.isExistUser(newNickName))
    {
        user.setWriteBuffer(fd, serverMessage(ERR_NICKNAMEINUSE, nickName, "", "", "Nickname is already in use"));
        return;
    }
    
    user.setNickName(fd, newNickName);
    
    if (user.isLogin(fd))
        user.setBroadCastMessageToAllUser(fullMessage);
}

bool validNickName(string newNickName)
{
    size_t len = newNickName.length();
    for (size_t i = 0; i < len; i++)
    {
        if (!(newNickName[i]  >= 65 && newNickName[i] <= 126) && !(newNickName[i]  >= 48 && newNickName[i] <= 57))
            return (false);
    }
    return (true);
}