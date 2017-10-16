## CVar.setCurrentConfig(name)
Set `name` as current config. You need to call this function first before you can use
`.setVar()`, `.getVar()`, `.addBind()`, `.removeBind()`, `.runBinds()`!

* `name` - `string` the config name.

## CVar.setConfigVar(config, var, value)
Set `value` for `var` in `config`.

* `config` - `string` the config name.
* `var` - `string` the config var name.
* `value` - can be every [supported type](https://www.lua.org/pil/2.html)

## CVar.getConfigVar(config, var)
Get the value of `var` from `config`.

* `config` - `string` the config name.
* `var` - `string` the config var name.

**return:** a [supported type](https://www.lua.org/pil/2.html) with the value of `name` if succeeded, `nil` otherwise.

## CVar.addConfigBind(config, name, key, clicked, callback)
Add a new key bind in `config`.

* `config` - `string` the config name.
* `name` - `string` the bind name.
* `key` - the virtual key code or key name, see [keys.md](https://github.com/ReactiioN1337/exec-info/blob/master/doc/keys.md)
* `clicked` - `boolean` if `true` the `callback` gets triggered when `WinAPI.isKeyClicked()` returns `true`. 
If `clicked` is `false` the `callback` gets triggered when `WinAPI.isKeyDown()` returns true.
* `callback` - `function` the callback function

## CVar.removeConfigBind(config, name)
Removes the bind `name` from `config`.

* `config` - `string` the config name.
* `name` - `string` the bind name.

## CVar.runConfigBinds(config)
Executes all callback functions from `config`.

* `config` - `string` the config name.

## CVar.setVar(name, value)
Set `value` for the var `name` in the current config.

* `name` - `string` the config var name.
* `value` - can be every [supported type](https://www.lua.org/pil/2.html)

## CVar.getVar(name)
Get the value of the var `name` from the current config.

* `name` - `string` the config var name.

**return:** a [supported type](https://www.lua.org/pil/2.html) with the value of `name` if succeeded, `nil` otherwise.

## CVar.addBind(name, key, clicked, callback)
Add a new key bind in the current config.

* `name` - `string` the bind name.
* `key` - the virtual key code or key name, see [keys.md](https://github.com/ReactiioN1337/exec-info/blob/master/doc/keys.md)
* `clicked` - `boolean` if `true` the `callback` gets triggered when `WinAPI.isKeyClicked()` returns `true`. 
If `clicked` is `false` the `callback` gets triggered when `WinAPI.isKeyDown()` returns true.
* `callback` - `function` the callback function

## CVar.removeBind(name)
Removes the bind `name` from the current config.

* `name` - `string` the bind name.

## CVar.runBinds()
Executes all callback functions from the current config.
