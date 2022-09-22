project "Engine"
	location "%{dirs.localdir}"
		
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	targetdir ("%{dirs.libdir}")
	targetname("%{prj.name}_%{cfg.buildcfg}")
	objdir ("%{dirs.intdir}")

	pchheader "stdafx.h"
	pchsource "stdafx.cpp"

	files {
		"%{dirs.srcdir}/Engine/**.h",
		"%{dirs.srcdir}/Engine/**.cpp",
		"%{dirs.srcdir}/Engine/**.hlsli",
		"%{dirs.srcdir}/Engine/**.hlsl",
		"%{dirs.extdir}/DirectXTex/DDSTextureLoader/DDSTextureLoader11.*",
	}

	includedirs {
		".",
		"./**",
		"%{dirs.extdir}/simpleson/",
		"%{dirs.extdir}/DirectXTex/DDSTextureLoader/",
	}

	libdirs { "%{dirs.libdir}" }	
	links { "simpleson", "d3d11.lib" }
	
	filter "files:**/DDSTextureLoader11.cpp"
	    flags {"NoPCH"}


	shadermodel("5.0")
	local shader_dir = resdir.engine .. "/Assets/Shaders/"
	-- HLSL files that don't end with 'Extensions' will be ignored as they will be
	-- used as includes

	filter("files:**.hlsl")
		flags("ExcludeFromBuild")
		shaderobjectfileoutput(shader_dir.."%{file.basename}"..".cso")

	filter("files:**.ps.hlsl")
		removeflags("ExcludeFromBuild")
		shadertype("Pixel")

	filter("files:**.vs.hlsl")
		removeflags("ExcludeFromBuild")
		shadertype("Vertex")

	-- Warnings as errors
	shaderoptions({"/WX"})

	--defines {
	--	'RESOURCE_DIR="' .. resdir.engine:gsub("%\\", "/") .. '/"',
	--}