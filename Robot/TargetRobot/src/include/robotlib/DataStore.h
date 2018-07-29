#pragma once

#include <string>
#include <vector>
#ifndef WIN32
#include "pthread.h"
#else
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
	void RegisterDataItem(std::string name, DataItem * item);
	DataItem * LookupDataItem(std::string name);
private:
	std::vector<DataItem *> DataItems;
	void Lock();
	void Unlock();
#ifdef WIN32
	HANDLE mutex;
#else
	pthread_mutex_t mutex;
#endif
};