#include <iostream>
#include "kernelinterface.hpp"

int main()
{
	KernelInterface Driver = KernelInterface("\\\\.\\test");

	ULONG address = Driver.GetClientAddress();

	std::cout << "client adresi= " << address << std::endl;

	while (true)
	{

	}
}
