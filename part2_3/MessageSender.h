#include <iostream>
#include "fstream"
#include <set>
#include <queue>
#include <string>
#include <stdexcept>
#include <mutex>

#define ADMIN_FILE_PATH "data.txt"
#define OUT_FILE_PATH "output.txt"

class MessageSender
{
public:
	// -- part 1
	void ShowMenu() const;
	void SighIn();
	void SighOut();
	void ConnectedUsers();
	// -- part 2
	void readAdminFile();
	// -- part 3
	void writeMessagesToUsersFile();

private:
	// -- part 1
	std::set<std::string> onlineUsers;
	// -- part 2
	std::queue<std::string> messageQueue;
	// -- next part
	std::mutex msgSe;
	std::mutex userSe;
};

