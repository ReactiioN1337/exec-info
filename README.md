Exec is an application which basically executes lua scripts but can be expanded duo the plugin system.

It supports 32 and 64 bit operation systems (Windows 7 or later) and has [LuaJIT](http://luajit.org/) as interpreter for lua.

## Installation
The installation is quite simple. Download the latest [release from the release page](https://github.com/ReactiioN1337/exec-info/releases) and extract it.
Download the necessary [dependencies](https://github.com/ReactiioN1337/exec-info/tree/master/dependencies) and move the `lua51.dll` into `exec/x86/x64` (depends which executable you want to use). Run the executable **once** to generate the plugin and script directories or create manually two folders called `plugins` and `scripts`. That's all!

## Your first script
Writing scripts in [lua](https://www.lua.org/manual/5.1/) is very easy. Checkout the references first if you're not familiar with lua!

**References:**
* [Lua 5.1 Reference Manual](https://www.lua.org/manual/5.1/)
* [LuaJIT References](http://luajit.org/index.html)

In order that the script file can be successfully executed you need to declare the function `onScriptTick`.
```lua
function onScriptTick()
  -- your code here
end
```

If you have custom data and/or resources which needs to be initialized once and before the actual script then you should declare also the function `onScriptInitialize`.
```lua
function onScriptInitialize()
  -- your code here
end

function onScriptTick()
  -- your code here
end
```

Keep in mind that both function have no parameters or return value!

## Changelog
* Version 1.0.0
  * changed to release
  * added export: `forceEngineShutdown()` to safe quit exec
  * fixed several bugs

* Version 0.1.0
  * updated easy_lua API
  * changed plugin directories from plugin32/64 to plugins


* Version 0.0.3
  * streaming [resources](https://github.com/ReactiioN1337/exec-info/tree/master/resource)


* Version 0.0.2
  * added `MOUSEEVENTF_XXXX` flags
  * added `manifest.json` check


* Version 0.0.1
  * initial release

## Credits
* [The whole team from Lua](https://www.lua.org/)
* [Mike Pall](https://github.com/MikePall) for his [LuaJIT](http://luajit.org) interpreter
* [Niels Lohmann](https://github.com/nlohmann) for his beautiful [JSON header for modern C++](https://github.com/nlohmann/json)
* [frk](https://github.com/frk1) for his [runtime string encryption using XOR](https://www.unknowncheats.me/forum/c-and-c/164273-xor-compile-time.html)
* [Chris Foster](https://github.com/c42f) for [his minimal, type safe printf replacement library for C++](https://github.com/c42f/tinyformat)
