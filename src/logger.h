#include <string>
#include <iostream>

class Logger
{
  private:
	static void log(const std::string& level, const std::string& message);

  public:
	Logger() = default;
	static void error(const std::string& message);
	static void info(const std::string& message);
	static void warning(const std::string& message);
	template <typename T> static T input(const std::string& prompt)
	{
		std::cout << std::left << std::setw(8) << "[INPUT]" << " -> ";
		T answer;
		std::cin >> answer;
		return answer;
	}
};