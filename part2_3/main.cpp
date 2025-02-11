#include <iostream>
#include <thread>
#include "MessageSender.h"

int main()
{
	int choise = 0;
	MessageSender program = MessageSender();
	std::thread t1(&MessageSender::readAdminFile, &program);
	std::thread t2(&MessageSender::writeMessagesToUsersFile, &program);
	while (true)
	{
		while (!(choise <= 4 && choise >= 1))
		{
			program.ShowMenu();
			std::cout << "enter your choise: ";
			std::cin >> choise;
		}
		switch (choise)
		{
		case 1:
			program.SighIn();
		case 2:
			program.SighOut();
		case 3:
			program.ConnectedUsers();
		case 4:
			exit(1);
		}
	}
	

	return 0;
}