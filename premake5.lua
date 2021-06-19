workspace "OpenGL"
    configurations { "Debug", "Release" }
    platforms { "linux64", "Win32" }
    location "build"

    includedirs {
        "libs/glad/include",
        "libs/GLFW/include"
    }

    cppdialect "C++17"

    filter "configurations:Debug"
        defines { "Debug" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDebug" }
        optimize "On"
    
    filter "platforms:linux64"
        system "linux"
        architecture "x86_64"
        links { 
            "dl", 
            "GL", 
            "X11", 
            "pthread"
        }

    filter "platforms:Win32"
        system "windows"
        architecture "x86_64"

    project "Triangle"
        kind "ConsoleApp"
        language "C++"
        location "build/Triangle"
        files { 
            "src/**.cpp", 
            "src/**.hpp", 
            "src/glad.c"
        }
        targetdir "bin"
        
        libdirs { "libs/GLFW/bin"}
        links { "glfw3" }
        

        