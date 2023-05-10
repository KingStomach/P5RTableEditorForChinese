#pragma once
#include <fstream>

enum class ReadError
{
	NOERR,
	OPENFAIL
};

#define RETURNERR(err) \
this->setError(err);\
return;

class IReader
{
public:
	IReader(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in)
		: m_reader(filename, mode), m_error(ReadError::NOERR) {}
	virtual ~IReader() { m_reader.close(); }
	IReader(const IReader&) = delete;
	IReader(IReader&&) = delete;
	IReader operator=(const IReader&) = delete;
	IReader operator=(IReader&&) = delete;

	virtual void read() = 0;
	ReadError hasError() const { return m_error; }

protected:
	void setError(ReadError err) { this->m_error = err; }
	std::ifstream& getReader() { return m_reader; }

private:
	std::ifstream m_reader;
	ReadError m_error;
};