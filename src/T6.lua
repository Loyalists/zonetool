T6 = {}

function T6:include()
    includedirs {
        path.join(ProjectFolder(), "T6")
    }
end

function T6:link()
    self:include()
	links {
		"T6"
	}
end

function T6:project()
    local folder = ProjectFolder();

    project "T6"
        kind "StaticLib"
        language "C++"
        
        pchheader "stdafx.hpp"
        pchsource(path.join(folder, "T6/stdafx.cpp"))

        files {
            path.join(folder, "T6/**.h"),
            path.join(folder, "T6/**.hpp"),
            path.join(folder, "T6/**.cpp")
        }

        self:include()
        H1:include()
        ZoneUtils:include()
        
        zstd:include()
        zlib:include()
end