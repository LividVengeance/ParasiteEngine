#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Parasite
{
	class PARASITE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log marcos
#define PE_CORE_FATAL(...)     ::Parasite::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define PE_CORE_ERROR(...)     ::Parasite::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_CORE_WARN(...)      ::Parasite::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_INFO(...)      ::Parasite::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_LOG(...)       ::Parasite::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define PE_FATAL(...)          ::Parasite::Log::GetClientLogger()->critical(__VA_ARGS__)
#define PE_ERROR(...)          ::Parasite::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_WARN(...)           ::Parasite::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_INFO(...)           ::Parasite::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_TRACE(...)          ::Parasite::Log::GetClientLogger()->trace(__VA_ARGS__)