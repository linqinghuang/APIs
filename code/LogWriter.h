/**************************************************************************************************
* File Name : LogWriter.h
* Created : 17 / 02 / 13
* Author : ChenZhongYu
* Model : LogWriter 
* Description : LogWriter接口声明
**************************************************************************************************/


/*
<LogWriter>
	<logwriter_savepath>D:/LogDir</logwriter_savepath>  //保存目录
	<logwriter_savedays>60</logwriter_savedays> //日志保存时长（day）
	<logwriter_logfilesize>10</logwriter_logfilesize> //单个日志文件大小（M）
	<logwriter_filter effective_type = "1">5</logwriter_filter> //日志级别：0 Fatal, 1 Error, 2 Warn, 3 Notice, 4 Info, 5 Debug, 6 Trace
	<logwriter_enable_console>1</logwriter_enable_console> // 是否同时打印日志到控制台：1 Enable， 0 Disable
	<logwriter_flush>1</logwriter_flush > // 日志是否立刻写入文件：1 Enable， 0 Disable
	<logwriter_new_file_when_start>1</logwriter_new_file_when_start> // 启动时是否新建日志文件：1 Enable， 0 Disable
	<logwriter_write_file_async>1</logwriter_write_file_async> // 异步写日志文件：1 Enable， 0 Disable
< / LogWriter>
*/


#pragma once
#include <string>


#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) || defined(_WINDOWS)
	#ifdef LOGWRITER_EXPORTS
		#define LOGWRITER_API __declspec(dllexport) 
	#else
		#define LOGWRITER_API __declspec(dllimport) 
		
		#if defined(_DEBUG) || defined(DEBUG)
			#if defined(WIN64) || defined(_WIN64)
				#pragma comment(lib, "LogWriter_x64d.lib")
			#else
				#pragma comment(lib, "LogWriterd.lib")
			#endif
		#else
			#if defined(WIN64) || defined(_WIN64)
				#pragma comment(lib, "LogWriter_x64.lib")
			#else
				#pragma comment(lib, "LogWriter.lib")
			#endif
		#endif
	#endif
#else
	#define LOGWRITER_API
#endif


namespace MRPS
{
	enum ELogLevel
	{
		LOG_SYSTEM = 0,
		LOG_ERROR = 1,
		LOG_WARN = 2,
		LOG_NOTICE = 3,
		LOG_INFO = 4,
		LOG_DEBUG = 5,
		LOG_TRACE = 6,
	};

	class LOGWRITER_API LogWriter
	{
	public:
		static void System(const ::std::string& strPlugName, const ::std::string& strLog);
		static void System(const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Error(const ::std::string& strPlugName, const ::std::string& strLog);
		static void Error(const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Warn(const ::std::string& strPlugName, const ::std::string& strLog);
		static void Warn(const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Notice(const ::std::string& strPlugName, const ::std::string& strLog);
		static void Notice(const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Info(const ::std::string& strPlugName, const ::std::string& strLog);
		static void Info(const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Debug(const ::std::string& strPlugName, const ::std::string& strLog);
		static void Debug(const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Trace(const ::std::string& strPlugName, const ::std::string& strLog);
		static void Trace(const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Log(ELogLevel level, const ::std::string& strPlugName, const ::std::string& strLog);
		static void Log(ELogLevel level, const ::std::string& strPlugName, const char* stringFormat, ...);

		static void Stop(bool force = false);
	};
}

#ifdef __cplusplus
extern "C"
{
#endif

	//LOGWRITER_API void LW_Init(const char* logDir/* = "D:\\LogDir"*/, MRPS::ELogLevel logLevel/* = LOG_DEBUG*/);
	LOGWRITER_API void LW_System(const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Error(const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Warn(const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Notice(const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Info(const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Debug(const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Trace(const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Log(MRPS::ELogLevel level, const char* strPlugName, const char* strLog);
	LOGWRITER_API void LW_Stop(bool force);

#ifdef __cplusplus
}
#endif