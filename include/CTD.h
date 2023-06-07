#pragma once
#include <array>
#include <type_traits>
#include <vector>

class CTD
{
public:
	using Head = std::array<uint8_t, 48>;
	using Data = std::vector<uint8_t>;
	using End = std::array<uint8_t, 16>;

	template <class Head, class Datas, class End>
	CTD(Head&& header, Datas&& data, End&& end) : m_header(std::forward<decltype(header)>(header)), m_data(std::forward<decltype(data)>(data)), m_end(std::forward<decltype(end)>(end)) {}

	template <class Fn>
	std::vector<typename std::invoke_result<Fn, Data>::type> decode(Fn&& fn) const
	{
		std::vector<typename std::invoke_result<Fn, Data>::type> res;
		for (const auto& data : m_data)
		{ res.emplace_back(fn(data)); }
		return res;
	}

	void replace(const std::vector<uint8_t>& data, int row) { m_data[row] = data; }

	template <class Fn, class Encode>
	void encode(const std::vector<Encode>& datas, Fn&& fn)
	{
		m_data.clear();
		for (const auto& data : datas)
		{ m_data.emplace_back(fn(data)); }
	}

private:
	Head m_header;
	std::vector<Data> m_data;
	End m_end;

	friend class CTDWrite;
};