#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

class Core
{
  private:
	std::filesystem::path getAppDataLocalPath();

  public:
	Core();
	bool authUser(const std::string filePath, const std::string login);
	void clearAppData();
};
