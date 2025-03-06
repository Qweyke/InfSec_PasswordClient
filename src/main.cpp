#include <iostream>
#include "logger.h"
#include "core.h"

int main()
{
	Logger::info("Launching...");
	Core core;

	while (1)
	{
		int inp;
		inp = Logger::input<int>("Awaiting command: ");

		switch (inp)
		{
			case 1:
			{
				core.clearAppData();
				break;
			}

			default:
			{
				return 1;
			}
		}
	}
}