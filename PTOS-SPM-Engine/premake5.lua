project "PTOS-SPM-Engine"
    location "PTOS-SPM-Engine"
    kind "StaticLib"
    staticruntime "on"
    
    language "C++"
    cppdialect "C++17"

    targetdir (cwd .. "/bin/" .. outputdir .. "/%{prj.name}")
    objdir (cwd .. "/bin-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        cwd .. "/%{prj.name}/src/**.h",
        cwd .. "/%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        cwd .. "/%{prj.name}/src",
        cwd .. "/%{prj.name}/libs/spdlog/include",
        cwd .. "/%{IncludeDir.GLFW}",
        cwd .. "/%{IncludeDir.GLAD}"
    }

    links {
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PTOS_PLATFORM_WINDOWS",
            "PTOS_BUILD_STATIC"
        }

    filter "configurations:Debug"
        defines {"PTOS_BUILD_DEBUG", "PTOS_ASSERTS", "PTOS_LOGGING"}
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "PTOS_BUILD_RELEASE"
        runtime "Release"
        optimize "on"
