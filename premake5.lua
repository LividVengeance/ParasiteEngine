workspace "ParasiteEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dir relative to solution dir (root dir)
IncludeDir = {}
IncludeDir["GLFW"] = "ParasiteEngine/Vendor/GLFW/include"
IncludeDir["Glad"] = "ParasiteEngine/Vendor/Glad/include"
IncludeDir["ImGui"] = "ParasiteEngine/Vendor/ImGui"

-- Add premake files
include "ParasiteEngine/Vendor/GLFW"
include "ParasiteEngine/Vendor/Glad"
include "ParasiteEngine/Vendor/ImGui"


project "ParasiteEngine"
	location "ParasiteEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	buildoptions 
	{ 
		"/utf-8",
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pepch.h"
	pchsource "ParasiteEngine/Source/pepch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PE_PLATFORM_WINDOWS",
			"PE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

		filter "configurations:Debug"
			defines "PE_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "PE_Release"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "PE_DIST"
			runtime "Release"
			optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	buildoptions 
	{ 
		"/utf-8",
	}

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"ParasiteEngine/Vendor/spdlog/include",
		"ParasiteEngine/Source",
	}

	links
	{
		"ParasiteEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PE_PLATFORM_WINDOWS",
		}

		filter "configurations:Debug"
			defines "PE_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "PE_Release"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "PE_DIST"
			runtime "Release"
			optimize "On"