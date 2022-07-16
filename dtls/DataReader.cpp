#include "DataReader.hpp"

namespace crispy
{
	DataReader::DataReader(std::byte *data, std::size_t size, std::size_t offset) : data(data), size(size), offset(offset), transaction(true), transactionOffset(0)
	{
	}

	void DataReader::startTransaction()
	{
		this->transaction = true;
		this->transactionOffset = this->offset;
	}

	bool DataReader::checkTransaction()
	{
		bool ok = this->transaction;
		if (!ok)
			this->offset = this->transactionOffset;
		return ok;
	}

	std::size_t DataReader::left()
	{
		return this->size - this->offset;
	}
}
