#ifndef __LOGWRITE_H__
#define __LOGWRITE_H__

#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <time.h>
#include <string.h>

using namespace std;

/* 打印 */
#ifndef _PRINTF
#define _PRINTF(level, fmt, ...) \
	do{\
		char l_szLog[8192] = {0};\
		char l_szTmp[8192] = {0};\
		sprintf(l_szTmp, "[%s][%s][%d]", __FILE__, __FUNCTION__, __LINE__);\
		sprintf(l_szLog, fmt, ##__VA_ARGS__);\
		strcat(l_szTmp, l_szLog);\
		LogWrite::Instance().WriteLog(l_szTmp, level, true);\
	}while(0)
#endif

#ifndef I_PRINTF
#define I_PRINTF(fmt, ...) _PRINTF(LEVEL_INFO, fmt, ##__VA_ARGS__)
#endif

#ifndef D_PRINTF
#define D_PRINTF(fmt, ...) _PRINTF(LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#endif

#ifndef T_PRINTF
#define T_PRINTF(fmt, ...) _PRINTF(LEVEL_TRACE, fmt, ##__VA_ARGS__)
#endif

#ifndef W_PRINTF
#define W_PRINTF(fmt, ...) _PRINTF(LEVEL_WARNING, fmt, ##__VA_ARGS__)
#endif

#ifndef E_PRINTF
#define E_PRINTF(fmt, ...) _PRINTF(LEVEL_ERROR, fmt, ##__VA_ARGS__)
#endif

#ifndef F_PRINTF
#define F_PRINTF(fmt, ...) _PRINTF(LEVEL_FATAL, fmt, ##__VA_ARGS__)
#endif


/* 日志输出内容最大长度 */
#define LOG_COMMENT_MAX_LEN		8192

/* 日志输出路径最大长度 */
#define LOG_PATH_MAX_LEN		256
#define LOG_FILE_NAME_MAX_LEN	128

/* 普通数组最大长度 */
#define NORMAL_STR_MAX_LEN		8192

/* 日志输出级别 */
#define LEVEL_INFO 			 0		// 记录日常显示信息
#define LEVEL_DEBUG 		 1		// 记录一些临时调试信息
#define LEVEL_TRACE 		 2		// 记录一些跟踪信息
#define LEVEL_WARNING 		 3 		// 记录警告信息
#define LEVEL_ERROR 		 4 		// 记录错误信息
#define LEVEL_FATAL 		 5		// 记录严重错误信息		


class LogWrite
{
public:
	LogWrite()
	{
		m_bDebug		= true;
		m_bFile			= false;
		m_bScreen		= true;
		m_bNeedPreFix	= true;
		memset(m_szBuffer, 0, sizeof(m_szBuffer));
		memset(m_szLogPath, 0, sizeof(m_szLogPath));
	};

	~LogWrite()
	{
	
	};

public:
	/* 设置日志输出路径 */
	void SetLogPath(const char* i_pcLogPath)
	{
		strncpy(m_szLogPath, i_pcLogPath, LOG_PATH_MAX_LEN);
	}

	/* 输出日志 */
	void WriteLog(const char* i_pcMsg, int i_nLevel, bool i_bFlush)
	{
		char l_szLevel[NORMAL_STR_MAX_LEN] = {0};
		bool l_bLog = true;

		switch(i_nLevel)
		{
			case LEVEL_INFO:
				sprintf(l_szLevel, "LOG[INFO]:");
				break;
			case LEVEL_DEBUG:
				sprintf(l_szLevel, "LOG[DEBUG]:");
				if(!m_bDebug)
					l_bLog = false;
				break;
			case LEVEL_TRACE:
				sprintf(l_szLevel, "LOG[TRACE]:");
				if(!m_bDebug)
					l_bLog = false;
				break;
			case LEVEL_WARNING:
				sprintf(l_szLevel, "LOG[WARNING]:");
				if(!m_bDebug)
					l_bLog = false;
				break;
			case LEVEL_ERROR:
				sprintf(l_szLevel, "LOG[ERROR]:");
				break;
			case LEVEL_FATAL:
				sprintf(l_szLevel, "LOG[FATAL]:");
				break;
			default :
				l_bLog = false;
				break;
		}

		if (l_bLog && m_bNeedPreFix)
		{
			strcat(l_szLevel, " ");
			strcat(l_szLevel, i_pcMsg);
			strcat(l_szLevel, "\n\r");

			time_t l_tNow = time(0);
			char l_szTime[64]; 
			strftime(l_szTime, sizeof(l_szTime), "%Y-%m-%d %H:%M:%S ", localtime(&l_tNow)); 

			strcat(m_szBuffer, l_szTime);
			strcat(m_szBuffer, l_szLevel);
		}
		else if (l_bLog && !m_bNeedPreFix)
		{
			strcat(m_szBuffer, i_pcMsg);
			strcat(m_szBuffer, "\n\r");
		}

		if (i_bFlush)
		{
			if (0 == strlen(m_szBuffer))
				return;

			if(m_bScreen)
				LogToScreen();

			if(m_bFile)
				LogToFile();
			
			memset(m_szBuffer, 0, sizeof(m_szBuffer));
		}
	}


public:
	/* 提供接口 */
	static LogWrite& Instance()
	{
		static LogWrite g_oInst;
		return g_oInst;
	}

public:
	inline void SetDebug(bool i_bDebug){m_bDebug = i_bDebug;};
	inline void SetToFile(bool i_bFile){m_bFile = i_bFile;};
	inline void SetToScreen(bool i_bScreen){m_bScreen = i_bScreen;};
	inline void SetNeedPreFix(bool i_bNeedPreFix){m_bNeedPreFix = i_bNeedPreFix;};

private:
	void LogToFile()
	{
		time_t l_tNow = time(0);
		char l_szTime[64]; 
		strftime(l_szTime, sizeof(l_szTime), "/log_%Y%m%d.log",localtime(&l_tNow));

		char l_szFileName[LOG_PATH_MAX_LEN] = {0};
		strncpy(l_szFileName, m_szLogPath, LOG_PATH_MAX_LEN);
		strcat(l_szFileName, l_szTime);

		FILE* l_fpFile = fopen(l_szFileName,"a+");
		if (NULL != l_fpFile)
		{
			fprintf(l_fpFile,"%s", m_szBuffer);
			fclose(l_fpFile);
		}
	}

	void LogToScreen()
	{
		printf("%s", m_szBuffer);
	}


private:
	char m_szBuffer[LOG_COMMENT_MAX_LEN];		/* log输出最大长度 */
	bool m_bDebug;								/* 是否输出debug信息 */
	bool m_bFile;								/* 是否输出到文件 */
	bool m_bScreen;								/* 是否输出到屏幕 */
	bool m_bNeedPreFix;							/* 是否需要输出时间 */
	char m_szLogPath[LOG_PATH_MAX_LEN];			/* log输出路径 */

};


#endif

