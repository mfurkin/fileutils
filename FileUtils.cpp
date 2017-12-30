/*
 * FileUtils.cpp
 *
 *  Created on: 30 дек. 2017 г.
 *      Author: Алёна
 */

#include "FileUtils.h"
std::string FILEUTILS_TAG="FileUtils";


int makeSureFileExists(const char* fname, int isFile, LoggerEngine* logger_ptr) {
	HANDLE findPath;
	WIN32_FIND_DATA findData;
	findPath = FindFirstFile(fname,&findData);
	int result = (findPath != INVALID_HANDLE_VALUE);
	if (result) {
		std::string fname_st(fname);
		logString(FILEUTILS_TAG,"Search successful fname:",fname_st,logger_ptr);
	} else {
		unsigned long errCode = GetLastError();
		logPtr(FILEUTILS_TAG,"Error during log opening error code=",errCode,logger_ptr);
		if (!(isFile))
			CreateDirectory(fname,NULL);
		else {
			HANDLE file;
			file = CreateFile(fname,GENERIC_WRITE | GENERIC_READ,0,NULL,CREATE_NEW,0,NULL);
			if (file != INVALID_HANDLE_VALUE)
				CloseHandle(file);
			else {
				errCode = GetLastError();
				logPtr(FILEUTILS_TAG,"Log file creating error, error code=",GetLastError(),logger_ptr);
			}
		}
	}
	FindClose(findPath);
	return result;
}

void getLogPath(char* dest, char* dirName, void* logger_ptr ) {
	SHGetFolderPath(NULL,CSIDL_APPDATA,NULL,SHGFP_TYPE_CURRENT,dest);
	makeSureFileExists(dest,FALSE,(LoggerEngine*)logger_ptr);
	strcat(dest,dirName);
	makeSureFileExists(dest,FALSE,(LoggerEngine*)logger_ptr);
}

void getLogFname(char* dest, char* dirName,  char* fname, void* logger_ptr) {
	getLogPath(dest, dirName, (LoggerEngine*)logger_ptr);
	strcat(dest,fname);
}
void logString(std::string& tag, std::string msg, std::string msg2,	LoggerEngine* logger_ptr) {
	if (logger_ptr)
		(*logger_ptr).logString(tag,msg,msg2);
}

void logPtr(std::string& tag, std::string msg, unsigned ptr, LoggerEngine* logger_ptr) {
	if (logger_ptr)
		(*logger_ptr).logPtr(tag,msg,ptr);
}
