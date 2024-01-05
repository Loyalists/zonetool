IW6 = {}

function IW6:include()
    includedirs {
        path.join(ProjectFolder(), "IW6")
    }
end

function IW6:link()
    self:include()
	links {
		"IW6"
	}
end

function IW6:project()
    local folder = ProjectFolder();

    project "IW6"
        kind "StaticLib"
        language "C++"
        
        pchheader "stdafx.hpp"
        pchsource(path.join(folder, "IW6/stdafx.cpp"))

        files {
            path.join(folder, "IW6/**.h"),
            path.join(folder, "IW6/**.hpp"),
            path.join(folder, "IW6/**.cpp")
        }

        self:include()
        H1:include()
        ZoneUtils:include()

        zstd:include()
        zlib:include()
end