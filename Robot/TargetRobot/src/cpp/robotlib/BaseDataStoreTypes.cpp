#include "robotlib/BaseDataStoreTypes.h"

void DataItemCounter::Reset()
{
	Lock();
	counter = 0;
	Unlock();
}

uint32_t DataItemCounter::Get()
{
	Lock();
	uint32_t temp = counter;
	Unlock();
	return temp;
}

void DataItemCounter::Increment()
{
	Lock();
	counter++;
	Unlock();
}

void DataItemCounter::Decrement()
{
	Lock();
	counter--;
	Unlock();
}

void DataItemInt::Set(int32_t value)
{
	Lock();
	value_ = value;
	Unlock();
}

int32_t DataItemInt::Get()
{
	Lock();
	int32_t temp = value_;
	Unlock();
	return temp;
}

void DataItemDouble::Set(double value)
{
	Lock();
	value_ = value;
	Unlock();
}

double DataItemDouble::Get()
{
	Lock();
	double temp = value_;
	Unlock();
	return temp;
}

void DataItemString::Set(std::string value)
{
	Lock();
	value_ = value;
	Unlock();
}

std::string DataItemString::Get()
{
	Lock();
	std::string temp = value_;
	Unlock();
	return temp;
}