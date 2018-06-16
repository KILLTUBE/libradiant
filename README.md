Welcome to libradiant

Random facts:
 - fork of GtkRadiant 1.6.5
 - this compiles to a libradiant.dll hence the name
 - libradiant.dll is started via [julia/radiant.jl](../blob/master/julia/radiant.jl)
 - the GTK widgets (cam, tex, xy, z, console) are replaced with ImGui docks
 - lots of GTK code left, work-in-progress to remove/replace that
 - once all GTK code is gone, lets think about port this to WebGL
 - everything shall be highly scriptable via Julia: https://julialang.org/
 - since Julia is used, you can make use of thousands of packages: https://pkg.julialang.org/
 - REPL integrated via ImGui editor, you can re-script libradiant while it runs 
 - CTRL+Enter to eval selected-text-only or eval everything, when nothing is selected
 - Console REPL is opened by default aswell, this allows REPL with tab-completion and history etc.
 - try hard to remove all shitty C/C++ dependencies, like GTK, libxml2...
 - try to make this easy to maintain/compile, by reducing dependencies... GtkRadiant was a hell to build on Win10/VS2017

Community / Help / Suggestions

Forum: https://killtube.org/forum.php
Discord: https://discordapp.com/invite/mqBchQZ

Donate / Support (plz?)

https://www.patreon.com/kungfooman
https://www.paypal.me/kungfooman/10