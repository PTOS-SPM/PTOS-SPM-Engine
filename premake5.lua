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
IncludeDir["glm"] = "PTOS-SPM-Engine/libs/glm"

RENDERER = "PTOS_RENDER_GL" -- GL | DX | VLK | DYNAMIC

include "PTOS-SPM-Engine/libs/glfw"
include "PTOS-SPM-Engine/libs/glad"
include "PTOS-SPM-Engine"

project "TestEngine"
    location "TestEngine"
    kind "ConsoleApp"
    staticruntime "on"

    language "C++"
    cppdialect "C++17"

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
        "%{IncludeDir.glm}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "PTOS-SPM-Engine/src"
    }

    links {
        "PTOS-SPM-Engine"
    }

    configurations "vs*"
        buildoptions { "/utf-8" } --fixes issue in fmt used by spdlog

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PTOS_PLATFORM_WINDOWS",
            RENDERER
        }

    filter "configurations:Debug"
        defines {"PTOS_BUILD_DEBUG", "PTOS_ASSERTS", "PTOS_LOGGING"}
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        defines "PTOS_BUILD_RELEASE"
        optimize "on"
