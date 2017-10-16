## Callback.add(groupName, name, callback)
Adds a callback to `groupName` if all params are valid.

* `groupName` - `string` the group name
* `name` - `string` the callback name
* `callback` - `function` the callback function

## Callback.remove(groupName, name)
Removes a callback from `groupName`.

* `groupName` - `string` the group name
* `name` - `string` the callback name

## Callback.removeGroup(groupName)
Removes all callbacks from `groupName` and `nil`-out the group table.

* `groupName` - `string` the group name

## Callback.exec(groupName, arg)
Executes all callbacks from `groupName`.

* `groupName` - `string` the group name
* `arg` - **optional** (*can be every [supported type](https://www.lua.org/pil/2.html)*)

