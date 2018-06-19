load_shader(shadername, texturename) = ccall( (:ffi_load_shader, libradiant), Ptr{Void}, (Cstring, Cstring), shadername, texturename)

type Shader
	id::Int
end

function load_shaders()
	path_tex = "c:/OpenSciTech/build/Debug/base/textures"

	path_concrete = path_tex * "/" * "concrete"
	filelist = readdir(path_concrete)

	for i in filelist
			texturepath = "textures" * "/" * "concrete" * "/" * i
			shaderpath = "textures" * "/" * "concrete" * "/" * filename(i)
			log(console, path_concrete * "/" * i)
			log(console, texturepath)
			log(console, shaderpath)
			
			
			load_shader(shaderpath, texturepath)
	end

	#filter(isdir, filelist)
end