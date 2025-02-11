#include "MessageSender.h"

//the fucntion print the menu
void MessageSender::ShowMenu() const
{
	std::cout << "1.Sign In\n2.Sigh Out\n3.Connected Users\n4.Exit" << std::endl;
}

//the function SighIn one user
void MessageSender::SighIn()
{
	std::string name = "";
	std::cin >> name;
	if (onlineUsers.find(name) != onlineUsers.end())//if he allready in we dont sigh him in again
	{
		throw  std::invalid_argument("The user is already online can't make him online twice");
	}
	
	onlineUsers.insert(name);
}

//the function sighOut one user
void MessageSender::SighOut()
{
	std::string name = "";
	std::cin >> name;
	if (onlineUsers.find(name) == onlineUsers.end())//if he allready out we dont sigh him out again
	{
		throw  std::invalid_argument("The user is already offline can't make him offline twice");
	}
	onlineUsers.erase(name);
}

//the function print all the connected users
void MessageSender::ConnectedUsers()
{
	int i = 0;
	for (auto it = onlineUsers.begin();it != onlineUsers.end();it++)
	{
		std::cout << i++ + 1 << " - " << it->operator[](i) << std::endl;
	}
}

//the function read from the admin file and put the message in an array(queue)
void MessageSender::readAdminFile()
{
	std::string msg = "";
	
	while (true)
	{
		std::fstream file(ADMIN_FILE_PATH, std::ios::in | std::ios::out);
		msgSe.lock();
		while (getline(file, msg))
		{
			messageQueue.push(msg);
		}
		msgSe.unlock();
		std::ofstream clearFile(ADMIN_FILE_PATH, std::ios::trunc);
		clearFile.close();
		_sleep(6000);
	}
}

//the function write all the admin messages to everyone
void MessageSender::writeMessagesToUsersFile()
{
	std::string msg = "";
	std::string fullMsg = "";
	std::fstream file(OUT_FILE_PATH, std::ios::in);
	while (true)
	{
		for (int i = 0;i < messageQueue.size();i++)
		{
			msgSe.lock();
			msg = messageQueue.front();//getting the first message
			messageQueue.pop();//remove it
			msgSe.unlock();
			for (auto it = onlineUsers.begin();it != onlineUsers.end();it++)
			{
				userSe.lock();
				fullMsg += it->data() + ': ' + msg;
				userSe.unlock();
			}
		}
		file << fullMsg;
		fullMsg = "";
	}
}
