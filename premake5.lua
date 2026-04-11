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
        "external/imgui/backends/imgui_impl_vulkan.cpp"
    }

    includedirs {
        "external/imgui",
        "external/imgui/backends",
        "external/vulkan-headers/include"
    }

    filter "toolset:gcc"
        buildoptions { "-Wall", "-Wextra", "-Wpedantic" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}

project "volk"
    kind "StaticLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files { "external/volk/volk.c" }

    includedirs { "external/volk", "external/vulkan-headers/include" }

project "raytracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files { "src/**.cpp" }

    includedirs {
        "include",
        "external/imgui",
        "external/imgui/backends",
        "external/volk",
        "external/vulkan-headers/include"
    }

    links { "imgui", "volk" }

    filter "system:windows"
        local sdk = os.getenv("VULKAN_SDK") or "C:/VulkanSDK/1.4.341.1"
        includedirs { sdk .. "/Include" }
        libdirs { sdk .. "/Lib", sdk .. "/Lib/mingw" }
        links { "vulkan-1" }

    filter "system:linux"
        local sdk = os.getenv("VULKAN_SDK") or (os.getenv("HOME") .. "/VulkanSDK/1.4.341.1/x86_64")
        includedirs { sdk .. "/include" }
        libdirs { sdk .. "/lib" }
        links { "vulkan" }

    filter "system:macosx"
        local sdk = os.getenv("VULKAN_SDK") or (os.getenv("HOME") .. "/VulkanSDK/1.4.341.1/macOS")
        includedirs { sdk .. "/include" }
        libdirs { sdk .. "/lib" }
        links { "vulkan" }

    filter "system:windows"
        links { "vulkan-1" }

    filter "system:linux"
        links { "vulkan" }

    filter "toolset:gcc"
        buildoptions { "-Wall", "-Wextra", "-Wpedantic" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}
