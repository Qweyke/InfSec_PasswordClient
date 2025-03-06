#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

#define FILE "db.json"
#define DIR "InfSec_PassClient"

enum class LogLevel
{
	INFO,
	WARNING,
	ERROR,
	DEBUG
};

bool authUser(const std::string filePath, const std::string login)
{
	std::ifstream dbFile(filePath);

	if (!dbFile.is_open())
	{
		throw std::exception("Client. Can't open data base file");
	}

	try
	{
		json dbJson = json::parse(dbFile);
	}
	catch (const std::exception& ex)
	{
		throw std::runtime_error(std::string("Client. Can't refractor data from data base file to json obj: ") + ex.what() + "\n");
	}
	return true;
}

std::filesystem::path getAppDataLocalPath()
{
	return std::filesystem::temp_directory_path().parent_path().parent_path();
}

std::string prettifyPath(const std::filesystem::path& path)
{
	std::string prettyPath = path.string();
	std::replace(prettyPath.begin(), prettyPath.end(), '\\', '/');
	return prettyPath;
}

void log(log level, const std::string& message)
{
	std::string logMessage = getCurrentTime() + " [" + logLevelToString(level) + "] " + message;
	std::cout << logMessage << std::endl;

	if (logToFile && logStream.is_open())
	{
		logStream << logMessage << std::endl;
	}
}

void clearAppData()
{
	std::cout << "Client. Clearing app data... \n\n";
	std::filesystem::path path = getAppDataLocalPath() / DIR;
	if (std::filesystem::exists(path))
	{
		std::cout << std::filesystem::remove_all(path) << " directories and files deleted \n\n";
	}
	else
		std::cout << "Client. Nothing to clean \n\n";
}

int main()
{
	std::cout << "App. Launch";
	try
	{
		std::filesystem::path appDirPath = getAppDataLocalPath() / DIR;
		std::filesystem::path jsonFile = appDirPath / FILE;

		if (!std::filesystem::exists(jsonFile))
		{
			if (!std::filesystem::exists(appDirPath))
			{

				std::cout << "Creating app directory \n\n";
				std::filesystem::create_directory(appDirPath);
				std::cout << "App dir path created: " << appDirPath << "\n\n";
			}

			json skeleton = { { "users", { { "admin", { { "password", "" } } } } } };

			std::cout << "Creating json skeleton \n\n";
			std::ofstream out(jsonFile);
			out << std::setw(4) << skeleton << std::endl;
			std::cout << "Json skeleton created at: " << prettifyPath(jsonFile) << "\n\n";
		}
		else
			std::cout << "App path " << prettifyPath(appDirPath) << "\n\n";

		clearAppData();
	}
	catch (const std::exception& ex)
	{
		std::cout << "App. Errors ocurred while executing \n\n";
		std::cout << ex.what() << "\n\n";
		return 1;
	}
	// while (1)
	// {
	// 	std::cout << "Welcome to \"Pass-check Client\"! \n";
	// 	std::cout << "Please, enter your login: \n";

	// 	std::string login;
	// 	std::cin >> login;
	// }
}