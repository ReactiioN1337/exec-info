#include <includes.hpp>

bool on_plugin_load( easy_lua* lua )
{
    /// <devnote>
    /// As long as you need the lua interface beside a function callback,
    /// you can call easy_lua::shared(). The default parameter is a nullptr
    /// which means that the static pointer does not get initialized!
    /// </devnote>
    easy_lua::shared( lua );
    
    /// <devnote>
    /// Do whatever you need to initialize your stuff here. If anything
    /// fails and the function returns false, the plugin will be unloaded!
    /// </devnote>
    



    return true;
}

void on_plugin_unload()
{
    /// <devnote>
    /// Do whatever you need to free/shutdown your stuff here.
    /// </devnote>
}

EASY_LUA_MAKE_PLUGIN( on_plugin_load, on_plugin_unload )
