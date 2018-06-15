gtk_events_pending() = ccall((:gtk_events_pending, "libgtk-win32-2.0-0.dll"), Cint, ())
gtk_main_iteration() = ccall((:gtk_main_iteration, "libgtk-win32-2.0-0.dll"), Cint, ())
gtk_main() = ccall((:gtk_main, "libgtk-win32-2.0-0.dll"), Void, ())

function gtk_step()
	while (gtk_events_pending() == Cint(1))
	
		# cant hurt
		Base.invokelatest(mainloop)	
	
		gtk_main_iteration()
	end
end

function gtk_start_timer()
	global gtk_timer = Timer(function(timer)
		try
			Base.invokelatest(mainloop)
			gtk_step()
		catch e
		end
	end, 0, 1 / 60)
end