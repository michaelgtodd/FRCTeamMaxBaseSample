#pragma once

#include <string>
#include <vector>
#ifndef WIN32
#include "pthread.h"
#else
#define NOMINMAX
#include <Windows.h>
#endif

class DataItem
{
	friend class DataStore;
public:
	std::string GetName();
protected:
	void Lock();
	void Unlock();
private:
	void SetName(std::string);
#ifdef WIN32
	HANDLE mutex;
#else
	pthread_mutex_t mutex;
#endif
	std::string name_;
};

class DataStore
{
public:
	static void RegisterDataItem(std::string name, DataItem * item);
	static DataItem * LookupDataItem(std::string name);
	static std::vector<DataItem *> LookupDataItemBeginsWith(std::string name);
private:
	static std::vector<DataItem *> DataItems;
	static void Lock();
	static void Unlock();
#ifdef WIN32
	static HANDLE mutex;
#else
	static pthread_mutex_t mutex;
#endif
};