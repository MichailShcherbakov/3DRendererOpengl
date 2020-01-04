#include "StdAfx.h"
#include "LogSystem.h"

#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp"
#include "boost/date_time.hpp"

void LogSystem::Msg(ETypeMessage type, std::string log, std::string file, std::string func, int line)
{
#ifdef DEBUG
	std::string msg;

	auto now = boost::posix_time::second_clock::local_time();
	auto h = now.time_of_day().hours();
	auto m = now.time_of_day().minutes();
	auto s = now.time_of_day().seconds();

	std::stringstream time;
	time 
		<< (h > 9 ? std::to_string(h) : '0' + std::to_string(h))
		<< ":" 
		<< (m > 9 ? std::to_string(m) : '0' + std::to_string(m))
		<< ":" 
		<< (s > 9 ? std::to_string(s) : '0' + std::to_string(s))
		<< "." 
		<< std::to_string(now.time_of_day().total_milliseconds()).erase(3, 6);

	switch (type)
	{
	case ETypeMessage::Log:
	{
		msg = "[" + time.str() + "] [Log] [" + func + "] [" + std::to_string(line) + "] " + log;
		break;
	}
	case ETypeMessage::Warning:
	{
		msg = "[" + time.str() + "] [Warning] [" + func + "] [" + std::to_string(line) + "] " + log;
		break;
	}
	case ETypeMessage::Success:
	{
		msg = "[" + time.str() + "] [Success] [" + func + "] [" + std::to_string(line) + "] " + log;
		break;
	}
	case ETypeMessage::Error:
	{
		msg = "[" + time.str() + "] [Error] [" + func + "] [" + std::to_string(line) + "] " + log;
		break;
	}
	case ETypeMessage::FatalError:
	{
		msg = "[" + time.str() + "] [Fatal Error] [" + func + "] [" + std::to_string(line) + "] " + log;
		break;
	}
	}
	WriteLog(msg);

	std::cout << msg << std::endl;
#endif // DEBUG
}

void LogSystem::WriteLog(std::string msg)
{
#ifdef DEBUG
	if (!gParams->gLogFile.fileIsCreated)
	{
		auto path = boost::filesystem::absolute("Logs");

		if (!boost::filesystem::exists(path))
			boost::filesystem::create_directory(path);

		auto now = boost::posix_time::second_clock::local_time();

		auto d = now.date().day();
		auto mm = now.date().month();
		auto h = now.time_of_day().hours();
		auto m = now.time_of_day().minutes();
		auto s = now.time_of_day().seconds();

		std::stringstream time;
		time << (d > 9 ? std::to_string(d) : '0' + std::to_string(d))
			<< "." << (mm > 9 ? std::to_string(mm) : '0' + std::to_string(mm))
			<< "." << now.date().year()
			<< '_' << (h > 9 ? std::to_string(h) : '0' + std::to_string(h))
			<< "." << (m > 9 ? std::to_string(m) : '0' + std::to_string(m))
			<< "." << (s > 9 ? std::to_string(s) : '0' + std::to_string(s));
		
		std::stringstream ss;
		ss << path.string()
			<< "\\Log_"
			<< time.str()
			<< ".txt";

		gParams->gLogFile.fileName = ss.str();
		gParams->gLogFile.fileIsCreated = true;
	}

	std::fstream file;
	file.open(gParams->gLogFile.fileName, std::ios::out | std::ios::ate);

	if (!file.is_open())
		throw std::runtime_error("Error: Can't write to log file");

	file << msg;
	file.close();
#endif // DEBUG
}
