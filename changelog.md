1.1.0 / 2017-11-18
==================
* :rocket: updated Lua API
  * :white_check_mark: httpRequest(server, file, contents[, post][, ssl])
    * `server` - (*string*) - The domain or IPv4 (example: `raw.githubusercontent.com` or `1.3.3.7`)
    * `file` - (*string*) - The requested file (example: `ReactiioN1337/exec-info/master/manifest.json`)
    * `contents` - (*string* or *nil*) - The HTTP POST/GET request data (example: `?user=admin`)
    * `post` - (*boolean* optional) - If true, the request is a HTTP POST
    * `ssl` - (*boolean* optional) - If true, the request goes through SSL
    * **returns:** The response as `string` if succeeded, `false` or `nil` otherwise

  * :white_check_mark: executeLuaCode(code)
    * `code` - (*string*) - The Lua code (example: `'print(1)'`
    * **returns:** `true` or `false`

  * :white_check_mark: executeCodeFromGithub(file[, gist])
    * `file` - (*string*) - The requested file (example: `ReactiioN1337/exec-info/master/manifest.json`)
    * `gist` - (*boolean* optional) - If true, the requested file is a git-gist-file
    * **returns:** `true` or `false`

1.0.0 / 2017-10-17
==================
* :ok_hand: changed public release
* :rocket: added export: `forceEngineShutdown()` to safe quit exec
* :bug: fixed several bugs

0.1.0 / 2017-10-16
==================
* :zap: updated easy_lua API
* :construction: changed plugin directories from plugin32/64 to plugins


0.0.3 / 2017-10-16
==================
* :rocket: streaming [resources](https://github.com/ReactiioN1337/exec-info/tree/master/resource)


0.0.2 / 2017-10-15
==================
* :rocket: added `MOUSEEVENTF_XXXX` flags
* :alien: added `manifest.json` check


0.0.1 / 2017-10-15
==================
* :tada: initial private release
