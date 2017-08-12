solution "rasterizer"
	configurations{"debug", "release"}

	location "../../windows/vs2017"
	targetdir "../../bin"
	language "C++"
	platforms "x64"

	includedirs {"../../include"}
	includedirs {"../../externals/include"}
	libdirs {"../../externals/lib"}
	links { "glew32", "glew32s", "SDL2", "SDL2main", "SDL2test", "openGL32"}

	project "rasterizer"
		kind "ConsoleApp"
		files { "../../include/**", "../../src/**" }

		configuration "debug"
			targetsuffix "-d" 
			defines { "_CRT_SECURE_NO_WARNINGS", "WIN32","_DEBUG", "DEBUG" }
			flags { "Symbols" }

		configuration "release"
			defines { "WIN32", "NDEBUG" }
			flags { "Optimize" }
