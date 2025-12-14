#include "Core/CoreHeaders.h"
#include "Utility.h"

namespace fw
{
	double getHighPrecisionTime()
	{
		unsigned __int64 freq;
		unsigned __int64 time;

		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		QueryPerformanceCounter((LARGE_INTEGER*)&time);

		double timeseconds = (double)time / freq;

		return timeseconds;
	}

	float getRunningTime()
	{
		static double startTime = getHighPrecisionTime();
		double currentTime = getHighPrecisionTime();

		return (float)(currentTime - startTime);
	}

	void outputMessage(const char* message, ...)
	{
#define MAX_MESSAGE 1024
		char szBuff[MAX_MESSAGE];

		va_list arg;
		va_start(arg, message);
		vsnprintf_s(szBuff, sizeof(szBuff), _TRUNCATE, message, arg);
		va_end(arg);

		szBuff[MAX_MESSAGE - 1] = 0; // vsnprintf_s might do this, but docs are unclear.

		OutputDebugString(szBuff);
	}

	char* loadCompleteFile(const char* filename, long* length)
	{
		char* fileContents = 0;

		FILE* fileHandle;
		errno_t error = fopen_s(&fileHandle, filename, "rb");

		if (fileHandle)
		{
			fseek(fileHandle, 0, SEEK_END);
			long size = ftell(fileHandle);
			rewind(fileHandle);

			fileContents = new char[size + 1];
			fread(fileContents, size, 1, fileHandle);
			fileContents[size] = 0;

			if (length)
				*length = size;

			fclose(fileHandle);
		}

		return fileContents; // This pointer needs to be deleted when no longer needed.
	}

} // namespace fw