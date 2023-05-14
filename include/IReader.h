#pragma once
#include <array>
#include <fstream>
#include <type_traits>
#include <string>
#include <vector>

template <class Derived>
class IReader
{
public:
	IReader() = default;
	virtual ~IReader() = default;

	auto readData() { return static_cast<Derived*>(this)->readImpl(); }
};

template <class Derived>
class IStreamReader : public IReader<IStreamReader<Derived>>, protected std::ifstream
{
public:
	IStreamReader(const std::string& filename, ios_base::openmode mode = ios_base::in)
		: IReader<IStreamReader<Derived>>(), std::ifstream(filename, mode) {}
	virtual ~IStreamReader() = default;

protected:
	friend class IReader<IStreamReader<Derived>>;
	auto readImpl() { return static_cast<Derived*>(this)->readImpl(); }
};

template <class Derived>
class IStreamStrReader : public IStreamReader<IStreamStrReader<Derived>>
{
public:
	IStreamStrReader(const std::string& filename)
		: IStreamReader<IStreamStrReader<Derived>>(filename, std::ios::in) {}
	virtual ~IStreamStrReader() = default;

protected:
	friend class IStreamReader<IStreamStrReader<Derived>>;
	auto initData() const { return static_cast<const Derived*>(this)->initDataImpl(); }
	auto handleToken(const std::string& line, auto& res) const { return static_cast<const Derived*>(this)->handleTokenImpl(line, res); }
	auto readImpl();
};

template <class Derived>
auto IStreamStrReader<Derived>::readImpl()
{
	std::string line;
	auto res = this->initData();
	while (!this->eof())
	{
		std::getline(*this, line);
		this->handleToken(line, res);
	}

	return res;
}

template <class Derived>
class IStreamBinReader :public IStreamReader<IStreamBinReader<Derived>>
{
public:
	IStreamBinReader(const std::string& filename)
		: IStreamReader<IStreamBinReader<Derived>>(filename, std::ios::in | std::ios::binary) {}
	virtual ~IStreamBinReader() = default;

protected:
	auto getHeadToken() { return static_cast<Derived*>(this)->getHeadTokenImpl(); }
	void getToken(std::vector<uint8_t>& token) { static_cast<Derived*>(this)->getTokenImpl(token); }
	auto getEndToken() { static_cast<Derived*>(this)->getEndTokenImpl(); }

	auto initData() const { return static_cast<const Derived*>(this)->initDataImpl(); }
	std::pair<uint32_t, uint32_t> handleHeadToken(const auto& head) const { return static_cast<const Derived*>(this)->handleHeadTokenImpl(head); }
	void handleToken(const std::vector<uint8_t>& token, auto& res) { static_cast<Derived*>(this)->handleTokenImpl(token, res); }
	void handleEndToken(const auto& end) { return static_cast<Derived*>(this)->handleEndTokenImpl(end); }

	auto readImpl();

	void getEndTokenImpl() {}
	friend class IStreamReader<IStreamBinReader<Derived>>;
};

template <class Derived>
auto IStreamBinReader<Derived>::readImpl()
{
	auto [size, num] = this->handleHeadToken(getHeadToken());
	auto res = this->initData();

	std::vector<uint8_t> token(size);
	for (size_t i = 0; i < num; i++)
	{
		this->getToken(token);
		this->handleToken(token, res);
	}

	if constexpr (!std::is_void<decltype(this->getEndToken())>::value)
		this->handleHeadToken(getEndToken());

	return res;
}