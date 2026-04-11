workspace "raytracer"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    cppdialect "C++23"
    location "build"
    toolset "gcc"

project "raytracer"
    kind "ConsoleApp"
    language "C++"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files { "src/**.cpp" }
    includedirs { "include" }

    filter "toolset:gcc"
        buildoptions { "-Wall", "-Wextra", "-Wpedantic" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}
