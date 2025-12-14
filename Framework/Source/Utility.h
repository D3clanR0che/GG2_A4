#pragma once

namespace fw
{
	double getHighPrecisionTime();
	float getRunningTime();
	void outputMessage(const char* message, ...);
	char* loadCompleteFile(const char* filename, long* length);

} // namespace fw