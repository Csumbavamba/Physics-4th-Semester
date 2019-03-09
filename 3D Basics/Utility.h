#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <WS2tcpip.h>
#include <string>
#include <strstream>

#define VALIDATE(a) if (!a) return (false)




class Utility
{
private:

	static Utility * instance;

	int screenWidth = 1024;
	int screenHeight = 768;

public:
	static Utility * GetInstance()
	{
		if (instance == NULL)
		{
			instance = new Utility();
		}
		return instance;
	}

	static int GetScreenWidth();
	static int GetScreenHeight();

	static void Update();

	static void ShutDown();

	
	//static std::string ToString(sockaddr_in socketAddress)
	//{
	//	//INET_ADDRSTRLEN - maximum length for IPv4 addresses
	//	char charAddress[INET_ADDRSTRLEN];
	//	inet_ntop(AF_INET, &socketAddress.sin_addr, charAddress, INET_ADDRSTRLEN);

	//	std::string stringAddress = charAddress;
	//	std::string port = std::to_string(ntohs(socketAddress.sin_port));
	//	std::string addressPort = stringAddress + ':' + port;

	//	return addressPort;
	//}

	template<typename T>
	static std::string ToString(const T& value)
	{
		std::strstream theStream;
		theStream << value << std::ends;
		return (theStream.str());
	}



};
