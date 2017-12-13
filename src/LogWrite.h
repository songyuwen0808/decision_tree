#ifndef __LOGWRITE_H__
#define __LOGWRITE_H__

#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <time.h>
#include <string.h>

using namespace std;

/* ��ӡ */
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


/* ��־���������󳤶� */
#define LOG_COMMENT_MAX_LEN		8192

/* ��־���·����󳤶� */
#define LOG_PATH_MAX_LEN		256
#define LOG_FILE_NAME_MAX_LEN	128

/* ��ͨ������󳤶� */
#define NORMAL_STR_MAX_LEN		8192

/* ��־������� */
#define LEVEL_INFO 			 0		// ��¼�ճ���ʾ��Ϣ
#define LEVEL_DEBUG 		 1		// ��¼һЩ��ʱ������Ϣ
#define LEVEL_TRACE 		 2		// ��¼һЩ������Ϣ
#define LEVEL_WARNING 		 3 		// ��¼������Ϣ
#define LEVEL_ERROR 		 4 		// ��¼������Ϣ
#define LEVEL_FATAL 		 5		// ��¼���ش�����Ϣ		


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
	/* ������־���·�� */
	void SetLogPath(const char* i_pcLogPath)
	{
		strncpy(m_szLogPath, i_pcLogPath, LOG_PATH_MAX_LEN);
	}

	/* �����־ */
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
	/* �ṩ�ӿ� */
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
	char m_szBuffer[LOG_COMMENT_MAX_LEN];		/* log�����󳤶� */
	bool m_bDebug;								/* �Ƿ����debug��Ϣ */
	bool m_bFile;								/* �Ƿ�������ļ� */
	bool m_bScreen;								/* �Ƿ��������Ļ */
	bool m_bNeedPreFix;							/* �Ƿ���Ҫ���ʱ�� */
	char m_szLogPath[LOG_PATH_MAX_LEN];			/* log���·�� */

};


#endif

