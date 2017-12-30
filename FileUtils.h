/*
 * FileUtils.h
 *
 *  Created on: 30 дек. 2017 г.
 *      Author: Алёна
 */

#ifndef FILEUTILS_H_
#define _WIN32_IE 0x0500
#include <shlobj.h>
#include "LoggerEngine.h"
#define FILEUTILS_H_

extern "C" __declspec(dllexport) void getLogPath(char* dest, char* dirName, void* logger_ptr );
extern "C" __declspec(dllexport) void getLogFname(char* dest, char* dirName,  char* fname, void* logger_ptr);
void logString(std::string& tag, std::string msg, std::string msg2, LoggerEngine* logger_ptr);
void logPtr(std::string& tag, std::string msg, unsigned ptr, LoggerEngine* logger_ptr);
typedef  void (*GetLogPathProc) (char* dest, char* dirName, void* logger_ptr );
typedef void (*GetLogFnameProc) (char* dest, char* dirName,  char* fname, void* logger_ptr);
#endif /* FILEUTILS_H_ */
