#include "CTDReader.h"
#include <array>

CTDReader::CTDReader(const std::string& filename) : IStreamBinReader<CTDReader>(filename) {}

CTDReader::Head CTDReader::getHeadTokenImpl()
{
	Head head;
	this->std::ifstream::read(reinterpret_cast<char*>(head.data()), head.size());
	return head;
}

void CTDReader::getTokenImpl(std::vector<uint8_t>& token)
{
	this->std::ifstream::read(reinterpret_cast<char*>(token.data()), token.size());
}

std::vector<std::vector<uint8_t>> CTDReader::initDataImpl() const
{
	return std::vector<std::vector<uint8_t>>();
}

std::pair<uint32_t, uint32_t> CTDReader::handleHeadTokenImpl(const Head& head) const
{
	uint32_t total_data_size = (head[36] << 24) + (head[37] << 16) + (head[38] << 8) + head[39];
	uint32_t total_num = (head[40] << 24) + (head[41] << 16) + (head[42] << 8) + head[43];
	return std::make_pair(total_data_size / total_num, total_num);
}

void CTDReader::handleTokenImpl(const std::vector<uint8_t>& token, std::vector<std::vector<uint8_t>>& data) const
{
	data.emplace_back(token);
}