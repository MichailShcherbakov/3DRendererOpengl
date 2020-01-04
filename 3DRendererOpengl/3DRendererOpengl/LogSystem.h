#ifndef _LOG_SYSTEM_H_
#define _LOG_SYSTEM_H_

#include <string>

enum class ETypeMessage : short
{
	Unknown = 0,
	Log,
	Success,
	Warning,
	Error,
	FatalError,
};

namespace LogSystem
{
	void Msg(ETypeMessage type, std::string log, std::string  file, std::string  func, int line);
	void WriteLog(std::string  msg);
};

#define MSG(type, msg) \
LogSystem::Msg(type, msg, __FILE__, __FUNCTION__, __LINE__);

#endif // _LOG_SYSTEM_H_

