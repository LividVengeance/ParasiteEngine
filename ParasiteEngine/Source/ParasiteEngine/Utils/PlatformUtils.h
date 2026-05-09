#pragma once

#include "string"

namespace Parasite
{
	class CFileDialogs
	{
	public:
		static std::string OpenFile(const char* InFilter);
		static std::string SaveFile(const char* InFilter);
	};
}