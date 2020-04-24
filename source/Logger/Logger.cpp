
#include <cburggie_Logger.h>
#include <iostream>
#include <string>

void cburggie::logger(const std::string & text) { std::cout << text << std::endl; }
void cburggie::logger(const char * text)
{
	std::cout << text << std::endl;
}
