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
        "external/imgui/backends/imgui_impl_vulkan.cpp",
        "external/imgui/backends/imgui_impl_glfw.cpp"
    }

    includedirs {
        "external/imgui",
        "external/imgui/backends",
        "external/vulkan-headers/include",
        "external/glfw/include"
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

project "glfw"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files {
        "external/glfw/src/null_init.c",
        "external/glfw/src/null_monitor.c",
        "external/glfw/src/null_window.c",
        "external/glfw/src/null_joystick.c",
        "external/glfw/src/context.c",
        "external/glfw/src/init.c",
        "external/glfw/src/input.c",
        "external/glfw/src/monitor.c",
        "external/glfw/src/vulkan.c",
        "external/glfw/src/window.c",
        "external/glfw/src/platform.c",
    }

    includedirs {
        "external/glfw/include"
    }

    filter "system:windows"
        files {
            "external/glfw/src/platform.c",
            "external/glfw/src/win32_init.c",
            "external/glfw/src/win32_joystick.c",
            "external/glfw/src/win32_monitor.c",
            "external/glfw/src/win32_time.c",
            "external/glfw/src/win32_thread.c",
            "external/glfw/src/win32_window.c",
            "external/glfw/src/wgl_context.c",
            "external/glfw/src/win32_module.c",
            "external/glfw/src/egl_context.c",
            "external/glfw/src/osmesa_context.c"
        }
        defines { "_GLFW_WIN32" }

    filter "system:linux"
        files {
            "external/glfw/src/x11_init.c",
            "external/glfw/src/x11_monitor.c",
            "external/glfw/src/x11_window.c",
            "external/glfw/src/xkb_unicode.c",
            "external/glfw/src/posix_time.c",
            "external/glfw/src/posix_thread.c",
            "external/glfw/src/glx_context.c",
            "external/glfw/src/linux_joystick.c"
        }
        defines { "_GLFW_X11" }
        links { "dl", "pthread" }

    filter "system:macosx"
        files {
            "external/glfw/src/cocoa_init.m",
            "external/glfw/src/cocoa_monitor.m",
            "external/glfw/src/cocoa_window.m",
            "external/glfw/src/cocoa_time.c",
            "external/glfw/src/nsgl_context.m",
            "external/glfw/src/posix_thread.c"
        }
        defines { "_GLFW_COCOA" }
        links { "objc" }

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
        "external/imgui",
        "external/imgui/backends",
        "external/volk",
        "external/vulkan-headers/include",
        "external/glfw/include"
    }

    links { "imgui", "volk", "glfw", "gdi32", "user32", "shell32", "advapi32", "ole32" }

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
