#include "core.h"
#include "logger.h"

#define FILE "db.json"
#define DIR "InfSec_PassClient"

Core::Core()
{
	try
	{
		std::filesystem::path appDirPath = getAppDataLocalPath() / DIR;
		std::filesystem::path jsonFile = appDirPath / FILE;

		if (!std::filesystem::exists(jsonFile))
		{
			if (!std::filesystem::exists(appDirPath))
			{

				Logger::info("Creating app directory...");
				if (std::filesystem::create_directory(appDirPath))
					Logger::info(std::string("App dir path created: " + appDirPath.string()));
				else
					throw std::runtime_error(std::string(("Can't create directory at " + appDirPath.string())));
			}

			json skeleton = { { "users", { { "ADMIN", { { "password", "" }, { "roles", { "admin", "user" } } } } } } };

			Logger::info(std::string("Creating " + std::string(FILE) + " ..."));
			std::ofstream out(jsonFile);
			out << std::setw(4) << skeleton << std::endl;
			Logger::info(std::string("Json skeleton created at: " + jsonFile.string()));
		}
		else
			Logger::info(std::string("App path: " + jsonFile.string()));

		// clearAppData();
	}
	catch (const std::exception& ex)
	{
		Logger::error("Errors ocurred while initializing core");
		Logger::error(ex.what());
	}
}

std::filesystem::path Core::getAppDataLocalPath()
{
	return std::filesystem::temp_directory_path().parent_path().parent_path();
}

void Core::clearAppData()
{
	Logger::info("Clearing app data...");
	std::filesystem::path path = getAppDataLocalPath() / DIR;
	if (std::filesystem::exists(path))
	{
		uint64_t dirsDeleted = std::filesystem::remove_all(path);
		Logger::info(std::string(std::to_string(dirsDeleted) + " directories and files deleted"));
	}
	else
		Logger::warning("Nothing to clean");
}

bool Core::authUser(const std::string filePath, const std::string login)
{
	std::ifstream dbFile(filePath);

	if (!dbFile.is_open())
	{
		throw std::exception("Can't open data base file");
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