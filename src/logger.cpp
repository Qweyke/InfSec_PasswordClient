#include "logger.h"
#include <iomanip>

void Logger::log(const std::string& level, const std::string& message)
{
	std::string lvl("[" + level + "]");
	std::cout << std::left << std::setw(8) << lvl << " -> " << message << "\n";
}

void Logger::error(const std::string& message)
{
	Logger::log("ERROR", message);
}

void Logger::info(const std::string& message)
{
	Logger::log("INFO", message);
}

void Logger::warning(const std::string& message)
{
	Logger::log("WARNING", message);
}