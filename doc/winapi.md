#
# WinAPI.isKeyDown(key)
* `key` - the virtual key code or key name, see [keys.md](https://github.com/ReactiioN1337/exec-info/blob/master/doc/keys.md)

**return:** `true` if `key` is down, `false` otherwise.

## WinAPI.isKeyClicked(key)
* `key` - the virtual key code or key name, see [keys.md](https://github.com/ReactiioN1337/exec-info/blob/master/doc/keys.md)

**return:** `true` if `key` was clicked, `false` otherwise.

## WinAPI.keyNameToVKey(keyName)
* `keyName` the key name, see [keys.md](https://github.com/ReactiioN1337/exec-info/blob/master/doc/keys.md)

**return:** the virtual key code as `number` if `keyName` was valid, `nil` otherwise.

## WinAPI.vkeyToKeyName(key)
* `key` the virtual key code, see [keys.md](https://github.com/ReactiioN1337/exec-info/blob/master/doc/keys.md)

**return:** the key name as `string` if `key` was valid, `nil` otherwise.

## WinAPI.sleep(time)
* `time` - the time in milliseconds as `number`

## WinAPI.mouseEvent(flags, dx, dy, data, extrainfo)
For more information about all parameters, [visit the msdn](https://msdn.microsoft.com/en-us/library/windows/desktop/ms646260(v=vs.85).aspx).
* `flags` - as `number` can be:
  * MOUSEEVENTF_MOVE
  * MOUSEEVENTF_LEFTDOWN
  * MOUSEEVENTF_LEFTUP
  * MOUSEEVENTF_RIGHTDOWN
  * MOUSEEVENTF_RIGHTUP
  * MOUSEEVENTF_MIDDLEDOWN
  * MOUSEEVENTF_MIDDLEUP
  
