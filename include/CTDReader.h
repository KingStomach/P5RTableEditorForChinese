#pragma once
#include "IReader.h"
#include <fstream>
#include <vector>

class CTDReader final : public IStreamBinReader<CTDReader>
{
public:
	CTDReader(const std::string& filename);
	~CTDReader() = default;

protected:
	using Head = std::array<unsigned char, 48>;

	Head getHeadTokenImpl();
	void getTokenImpl(std::vector<uint8_t>& token);
	std::vector<std::vector<uint8_t>> initDataImpl() const;
	std::pair<uint32_t, uint32_t> handleHeadTokenImpl(const Head& head) const;
	void handleTokenImpl(const std::vector<uint8_t>& token, std::vector<std::vector<uint8_t>>& data) const;

	friend class IStreamBinReader<CTDReader>;
};