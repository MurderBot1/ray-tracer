workspace "raytracer"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    cppdialect "C++23"
    location "build"
    toolset "gcc"

project "imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files {
        "external/imgui/imgui.cpp",
        "external/imgui/imgui_draw.cpp",
        "external/imgui/imgui_tables.cpp",
        "external/imgui/imgui_widgets.cpp",
        "external/imgui/imgui_demo.cpp",
        "external/imgui/imconfig.h",
        "external/imgui/imgui.h",
        "external/imgui/imgui_internal.h",
        "external/imgui/imstb_rectpack.h",
        "external/imgui/imstb_textedit.h",
        "external/imgui/imstb_truetype.h"
    }

    includedirs {
        "external/imgui"
    }

    filter "toolset:gcc"
        buildoptions { "-Wall", "-Wextra", "-Wpedantic" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}
    
project "raytracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files { "src/**.cpp" }

    includedirs {
        "include",
        "external/imgui"
    }

    links { "imgui" }

    filter "toolset:gcc"
        buildoptions { "-Wall", "-Wextra", "-Wpedantic" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}
