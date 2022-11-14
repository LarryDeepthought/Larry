#include "Scraper.hpp"
#include "Useful.hpp"

#include <vector>
#include <iostream>

using namespace std;

Scraper::Scraper(uint16_t day, uint16_t year)
{
	fstream configJsonFile;
	stringstream buffer;

	configJsonFile.open(ConfigJsonLocation);
	configJsonFile >> ConfigJson;
	
	// buffer << configJsonFile.rdbuf();
	// configJsonFile.close();

	// ConfigJson = nlohmann::json::parse(buffer.str());

	cout << GetLastMessage() << endl;
	/*
	ActivatePythonScraper();
	while (!PythonScraperIsFinished());
	WebsiteData = GetPythonScraperResponse();
	*/
}

void Scraper::SendMessage(string message)
{
	string finalMessage;
	
	// Formatting
	finalMessage = get_json_value(ConfigJson["Communication"]["Formatting"]["Prefix"]) +
				   message + 
				   get_json_value(ConfigJson["Communication"]["Formatting"]["Postfix"]);
	
	fstream communicationFile = OpenCommunicationFile();
	communicationFile << finalMessage;
	communicationFile.close();
}

string Scraper::GetLastMessage()
{
	string communicationFileData = GetCommunicationFileData();

	// splitting the messages
	vector<string> messages;
	string delimiter = get_json_value(ConfigJson["Communication"]["Formatting"]["Postfix"]);
	size_t pos = 0;
	while ((pos = communicationFileData.find(delimiter)) != string::npos)
	{
		messages.push_back(communicationFileData.substr(0, pos));
		communicationFileData.erase(0, pos + delimiter.length());
	}
	messages.push_back(communicationFileData);

	// finding the last message
	size_t originIndex = ConfigJson["Communication"]["Formatting"]["Parameters"]["Origin"];
	string parameterDelimiters[2] = { get_json_value(ConfigJson["Communication"]["Formatting"]["ParameterStart"]),
									  get_json_value(ConfigJson["Communication"]["Formatting"]["ParameterEnd"]) };
	messages.reserve(); // reordering so the last messages are on top
	for (string message : messages)
	{
		pos = 0;
		for (size_t i = 0; i < originIndex; i++)
			pos = message.find(parameterDelimiters[0], pos + 1);
		string messageOrigin = message.substr(pos + 1, message.find(parameterDelimiters[1], pos) - pos - 1);
		if (messageOrigin == get_json_value(ConfigJson["Communication"]["Origins"]["WebScraper"]))
		{
			string prefix = get_json_value(ConfigJson["Communication"]["Formatting"]["Prefix"]);
			return message.substr(message.find(prefix) + prefix.length(), string::npos);
		}
	}

	return "NO_MSG";
}

fstream Scraper::OpenCommunicationFile()
{
	fstream file;
	file.open(ConfigJson["Communication"]["CommunicationFileLocation"]);
	return file;
}

string Scraper::GetCommunicationFileData()
{
	stringstream buffer;
	buffer << OpenCommunicationFile().rdbuf();
	return buffer.str();
}

void Scraper::ActivatePythonScraper()
{

}