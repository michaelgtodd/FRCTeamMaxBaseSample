#pragma once
#include "DataStore.h"

class DataItemCounter : public DataItem
{
public:
	void Reset();
	uint32_t Get();
	void Increment();
	void Decrement();
private:
	uint32_t counter = 0;
};

class DataItemInt : public DataItem
{
public:
	void Set(int32_t value);
	int32_t Get();
private:
	int32_t value_;
};

class DataItemDouble : public DataItem
{
public:
	void Set(double value);
	double Get();
private:
	double value_;
};

class DataItemString : public DataItem
{
public:
	void Set(std::string value);
	std::string Get();
private:
	std::string value_;
};