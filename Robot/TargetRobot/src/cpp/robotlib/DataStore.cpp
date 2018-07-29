#include "robotlib/DataStore.h"
#include <iostream>


#ifdef WIN32
HANDLE DataStore::mutex;
#else
pthread_mutex_t DataStore::mutex;
#endif

std::vector<DataItem *> DataStore::DataItems;

void DataItem::Lock()
{
#ifdef WIN32
	WaitForSingleObject(mutex, INFINITE);
#else
	pthread_mutex_lock(&mutex);
#endif
}

void DataItem::Unlock()
{
#ifdef WIN32
	ReleaseMutex(mutex);
#else
	pthread_mutex_unlock(&mutex);
#endif
}

void DataItem::SetName(std::string name)
{
	name_ = name;
}

std::string DataItem::GetName()
{
	return name_;
}

void DataStore::RegisterDataItem(std::string name, DataItem * item)
{
	Lock();
	item->SetName(name);

	for (std::vector<DataItem *>::iterator i = DataItems.begin();
		i != DataItems.end();
		i++)
	{
		if ((*i)->GetName() == name)
		{
			Unlock();
			std::cout << "Failed to register duplicate data item: " << name << std::endl;
			return;
		}
	}

	DataItems.push_back(item);
	Unlock();
}

DataItem * DataStore::LookupDataItem(std::string name)
{
	Lock();
	for (std::vector<DataItem *>::iterator i = DataItems.begin();
		i != DataItems.end();
		i++)
	{
		if ((*i)->GetName() == name)
		{
			Unlock();
			return (*i);
		}
			
	}

	Unlock();
	std::cout << "Failed to lookup DataStore Item: " << name << std::endl;
	return NULL;
	
}

std::vector<DataItem *> DataStore::LookupDataItemBeginsWith(std::string name)
{
	Lock();
	std::vector<DataItem *> temp;	
	
	for (std::vector<DataItem *>::iterator i = DataItems.begin();
		i != DataItems.end();
		i++)
	{
		if ((*i)->GetName().compare(0, name.length(), name) == 0)
			temp.push_back((*i));
	}

	Unlock();
	return temp;
}

void DataStore::Lock()
{
#ifdef WIN32
	WaitForSingleObject(mutex, INFINITE);
#else
	pthread_mutex_lock(&mutex);
#endif
}

void DataStore::Unlock()
{
#ifdef WIN32
	ReleaseMutex(mutex);
#else
	pthread_mutex_unlock(&mutex);
#endif
}