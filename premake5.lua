workspace "Chopp"
    platforms { "Win64", "Win32" }
    configurations {"Debug", "Release"}

    language "C++"
    cppdialect "C++20"

    filter "platforms:Win32"
        system "Windows"
        architecture "x86"

    filter "platforms:Win64"
        system "Windows"
        architecture "x64"

    filter "configurations:Debug"
        -- Add preprocessor definition DEBUG to compiler
        defines {"DEBUG"}
        -- Enable debugging symbols
        symbols "On"
    
    filter "configurations:Release"
        defines {"RELEASE"}
        -- Turn on dat optimization
        optimize "On"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

runtime_debug = {"sfml-system-d-2", "sfml-window-d-2", "sfml-graphics-d-2", "sfml-audio-d-2", "sfml-network-d-2"}

project "Chopp"
    location "src"
    kind "ConsoleApp"

    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir)

    pchheader "chpch.hpp"
	pchsource "src/chpch.cpp" -- Only used by MSVC

    files
    {
        "src/**.hpp",
        "src/**.cpp",
    }

    includedirs
    {
        "vendor/SFML/install/include",
        --"vendor/spdlog/include",
    }

    libdirs
    {
        "vendor/SFML/install/lib"
    }

    filter "configurations:Debug"
        links
        {
            "sfml-graphics-d.lib",
            "sfml-window-d.lib",
            "sfml-system-d.lib",
        }

    filter "configurations:Release"
        links
        {
            "sfml-graphics.lib",
            "sfml-window.lib",
            "sfml-system.lib",
        }

    postbuildcommands
    {
        ("{COPY} ../vendor/SFML/install/bin/*-d-2.dll " .. "../bin/" .. outputdir)
    }

