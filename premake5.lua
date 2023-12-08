workspace "PTOS-SPM"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release"
    }

cwd = path.getabsolute(".")
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "PTOS-SPM-Engine/libs/glfw/include"
IncludeDir["GLAD"] = "PTOS-SPM-Engine/libs/glad/include"

include "PTOS-SPM-Engine/libs/glfw"
include "PTOS-SPM-Engine/libs/glad"

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

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/libs/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}"
    }

    links {
        "GLFW",
        "GLAD",
        "opengl32.lib"
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
        defines {"PTOS_BUILD_DEBUG", "PTOS_ASSERTS", "PTOS_LOGGING"}
        staticruntime "off"
        runtime "Debug"
        symbols "ON"
        
    filter "configurations:Release"
        defines "PTOS_BUILD_RELEASE"
        staticruntime "off"
        runtime "Release"
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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
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
        defines {"PTOS_BUILD_DEBUG", "PTOS_ASSERTS", "PTOS_LOGGING"}
        staticruntime "off"
        runtime "Debug"
        symbols "ON"
        
    filter "configurations:Release"
        staticruntime "off"
        runtime "Release"
        defines "PTOS_BUILD_RELEASE"
        optimize "ON"
