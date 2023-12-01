workspace "PTOS-SPM"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PTOS-SPM-Engine"
    location "PTOS-SPM-Engine"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    pchheader "ptospch.h"
    pchsource "%{prj.name}/src/ptospch.cpp"

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/libs/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PTOS_PLATFORM_WINDOWS",
            "PTOS_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/TestEngine")
        }

    filter "configurations:Debug"
        defines "PTOS_DEBUG"
        symbols "ON"

    filter "configurations:Release"
        defines "PTOS_RELEASE"
        optimize "ON"

project "TestEngine"
    location "TestEngine"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "PTOS-SPM-Engine/libs/spdlog/include",
        "PTOS-SPM-Engine/src"
    }

    links {
        "PTOS-SPM-Engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PTOS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PTOS_DEBUG"
        symbols "ON"

    filter "configurations:Release"
        defines "PTOS_RELEASE"
        optimize "ON"
