#pragma once

#include <cstddef>
#include <cstring>
#include "Helper.h"

class DataReader
{
public:
	DataReader(std::byte* data, std::size_t size, std::size_t offset = 0) : data(data), size(size), offset(offset), transaction(true), transactionOffset(0)
	{
		
	}

	void startTransaction()
	{
		this->transaction = true;
		this->transactionOffset = this->offset;
	}

	bool checkTransaction()
	{
		bool ok = this->transaction;
		if (!ok)
			this->offset = this->transactionOffset;
		return ok;
	}

	template<typename T>
	T read()
	{
		T t{};

		std::size_t tLen = sizeof(T);
		if (tLen + this->offset > this->size)
		{
			this->transaction = false;
			//dtls::Helper::error("Not enough data");
		}
		else
		{
			std::memcpy(&t, this->data + this->offset, tLen);
			this->offset += tLen;
		}

		return t;
	}
	
	template<typename T>
	void read(std::vector<T> &readData)
	{
		std::size_t size = readData.size() * sizeof(T);
		if (size > left())
		{
			this->transaction = false;
		}

		std::memcpy(readData.data(), this->data + this->offset, size);
	}

	template<typename T>
	void read(std::vector<T>& readData, std::size_t size)
	{
		readData.resize(size / sizeof(T));
		read(readData);
	}

	template<typename T>
	void read(T* readData, std::size_t size)
	{
		if (size > left())
		{
			this->transaction = false;
		}

		std::memcpy(readData, this->data + this->offset, size);
	}

	std::size_t left()
	{
		return this->size - this->offset;
	}

private:
	std::byte* data;
	std::size_t offset;
	std::size_t transactionOffset;
	std::size_t size;
	bool transaction;
};