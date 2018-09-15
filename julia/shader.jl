load_shader(shadername, texturename) = ccall( (:ffi_load_shader, libradiant), Ptr{Void}, (Cstring, Cstring), shadername, texturename)

type Shader
	id::Int
end

function load_shader_dir(foldername)
	try
		# todo: get rid of hardcoded path here and just use vfs?
		# like addPath(vfs, "c:/OpenSciTech/build/Debug/base/textures")
		#path_tex = "c:/OpenSciTech/build/Debug/base/textures"
		path_tex = "C:/xampp/htdocs/libwebgame_assets/libwebgame/textures"

		path_concrete = path_tex * "/" * foldername
		filelist = readdir(path_concrete)

		for i in filelist
				texturepath = "textures" * "/" * foldername * "/" * i
				shaderpath = "textures" * "/" * foldername * "/" * filename(i)
				#log(console, path_concrete * "/" * i)
				#log(console, texturepath)
				#log(console, shaderpath)
				
				
				log(console, shaderpath, texturepath)
				load_shader(shaderpath, texturepath)
		end

		#filter(isdir, filelist)
	catch ex
		log(console, "Exception in load_shader_dir: ", ex)
	end
end

# this doesnt work anymore, use load_shaders()
function textures()
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "blood")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "concrete")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "env")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "japan")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "kungtile")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "liquids")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "mymap")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "other")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "radiant")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "tools")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "window")
end

function load_shaders()
	load_shader_dir(".")
	load_shader_dir("blood")
	load_shader_dir("concrete")
	load_shader_dir("env")
	load_shader_dir("japan")
	load_shader_dir("kungtile")
	load_shader_dir("liquids")
	load_shader_dir("mymap")
	load_shader_dir("other")
	load_shader_dir("radiant")
	load_shader_dir("tools")
	load_shader_dir("window")
end