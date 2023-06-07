#pragma once
#include "Chat.h"
#include "ChatLibrary.h"
#include "CTD.h"

class CTDWrite final
{
public:
	CTDWrite() = delete;

	template <class OStream>
	static void write(OStream&& stream, const CTD& ctd)
	{
		uint32_t total_data_size = (ctd.m_header[36] << 24) + (ctd.m_header[37] << 16) + (ctd.m_header[38] << 8) + ctd.m_header[39];
		uint32_t total_num = (ctd.m_header[40] << 24) + (ctd.m_header[41] << 16) + (ctd.m_header[42] << 8) + ctd.m_header[43];
		stream.write((char*)ctd.m_header.data(), ctd.m_header.size());
		for (const auto& data : ctd.m_data)
		{
			stream.write((char*)data.data(), total_data_size / total_num);
		}
		int offset = (ctd.m_header[8] << 24) + (ctd.m_header[9] << 16) + (ctd.m_header[10] << 8) + ctd.m_header[11];
		stream.seekp(offset);
		stream.write((char*)ctd.m_end.data(), ctd.m_end.size());
		return;
	}
};