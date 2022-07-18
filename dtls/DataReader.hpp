#pragma once

#include <cstddef>
#include <vector>
#include <cstring>
#include "Helper.hpp"

namespace crispy
{
	class DataReader
	{
	public:
		DataReader(std::byte *data, std::size_t size, std::size_t offset = 0);

		void startTransaction();

		bool checkTransaction();

		template <typename T>
		T read()
		{
			T t{};

			std::size_t tLen = sizeof(T);
			if (tLen > left())
			{
				this->transaction = false;
				return t;
				// dtls::Helper::error("Not enough data");
			}

			std::memcpy(&t, this->data + this->offset, tLen);
			this->offset += tLen;
			

			return t;
		}

		template<typename T>
		void read(std::vector<T> &readData)
		{
			std::size_t byteSize = readData.size() * sizeof(T);
			read(readData.data(), byteSize);
		}

		template<typename T>
		void read(std::vector<T> &readData, std::size_t byteSize)
		{
			if (byteSize % sizeof(T) != 0)
			{
				this->transaction = false;
				return;
			}

			std::size_t size = byteSize / sizeof(T);
			readData.resize(size);
			read(readData.data(), byteSize);
		}

		template<typename T>
		void read(T *readData, std::size_t byteSize)
		{
			if (byteSize > left())
			{
				this->transaction = false;
			}

			std::memcpy(readData, this->data + this->offset, byteSize);
			this->offset += byteSize;
		}

		std::size_t left();

	private:
		std::byte *data;
		std::size_t offset;
		std::size_t transactionOffset;
		std::size_t size;
		bool transaction;
	};
}