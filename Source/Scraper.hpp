#include <string>
#include "json.hpp"
#include <fstream>

class Scraper
{
private:
	// Parameters
	nlohmann::json ConfigJson;
	std::string WebsiteData;
	const std::string ConfigJsonLocation = "Z:/PC/Dev/Programming Fun/Larry/Config.json";

	// Methods
	void SendMessage(std::string message);
	std::string GetLastMessage();
	std::string GetCommunicationFileData();
	std::fstream OpenCommunicationFile();

	void ActivatePythonScraper();
	bool PythonScraperIsFinished();
	std::string GetPythonScraperResponse();

public:
	// Constructor
	Scraper(uint16_t day, uint16_t year);
	std::string GetWebsite();
};	