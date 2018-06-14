function mainloop()::Void

	try
		#log(console, "hai")
		runthreads()
	catch ex
		log(console, ex)
	end

	nothing
end