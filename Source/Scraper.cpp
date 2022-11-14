#include "Scraper.hpp"
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

	GetLastMessage();
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
	finalMessage = ConfigJson["Communication"]["Formatting"]["Prefix"].dump() +
				   message + 
				   ConfigJson["Communication"]["Formatting"]["Postfix"].dump();
	
	fstream communicationFile = OpenCommunicationFile();
	communicationFile << finalMessage;
	communicationFile.close();
}

string Scraper::GetLastMessage()
{
	//string communicationFileData = GetCommunicationFileData();
	string communicationFileData = "{11:20:17}{Python}HelloWorld!\n{11:21:28}{CPP}HelloWorld!\n{10:23:-2}{Python}I travelled in time!";

	// splitting the messages
	vector<string> messages;
	string delimiter = ConfigJson["Communication"]["Formatting"]["Postfix"].dump();
	delimiter = delimiter.substr(1, delimiter.length() - 2);
	size_t pos = 0;
	while ((pos = communicationFileData.find(delimiter)) != string::npos)
	{
		messages.push_back(communicationFileData.substr(0, pos));
		communicationFileData.erase(0, pos + delimiter.length());
	}
	messages.push_back(communicationFileData);

	// finding the last message
	string messagePrefix = ConfigJson["Communication"]["Formatting"]["Postfix"];
	size_t originIndex = 0;
	size_t originPosition = messagePrefix.find("Origin");
	char parameterDelimiters[2] = {ConfigJson["ParameterStart"].dump()[1],
									ConfigJson["ParameterEnd"].dump()[1]	};
	pos = 0;
	while ((pos = messagePrefix.find(parameterDelimiters[1], pos + 1) < originPosition))
		originIndex++;
	size_t index;
	for (string message : messages)
	{
		index = 0;
		pos = 0;
		while (index < originIndex)
		{
			pos = message.find(parameterDelimiters[0], pos + 1);
			index++;
		}
		message = message.substr(pos, message.find(parameterDelimiters[1]) - pos);
		cout << message << endl;
	}

	return "";
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