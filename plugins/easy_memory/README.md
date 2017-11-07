## Process.attach(processId | processName)
Attaches to a process. The parameter has to be `processId` or `processName`.
- `processId` (*integer*) - The process id of the specified process
- `processName` (*string*) - The name of the process with `.exe` as prefix

**Return:** `true` if the process does exist and if [OpenProcess](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684320) succeeds, `false` or `nil` otherwise.

## Process.isRunning()
Determines if the attached process is still running.

**Return:** `true` if the exit code of the attached process returns `STILL_ACTIVE` using [GetExitCodeProcess](https://msdn.microsoft.com/en-us/library/windows/desktop/ms683189), `false` or `nil` otherwise.

## Process.getImage(name)
Get an image of a module.
- `name` (*string*) - The name of the module (example: `kernel32.dll`)

**Return:** a custom metatable (userdata) called `Image` if succeeded, `nil` otherwise.

## Process.read(address)
Reads *data* from an area of memory in a specified process.

- `address`(*integer*) - Address to the memory area

**Return:** A custom metatable (userdata) called `CReadProcessMemory` and contains
the following functions:
- `:bool()`
- `:char()`
- `:double()`
- `:float()`
- `:int8()`
- `:int16()`
- `:int32()`
- `:int64()`
- `:intptr()`
- `:uint8()`
- `:uint16()`
- `:uint32()`
- `:uint64()`
- `:uintptr()`
- `:string(length)`
  - `length` (*integer*) - The length of the string to read

## Process.write(address)
Writes *data* to an area of memory in a specified process.
- `address`

**Return:** A custom metatable (userdata) called `CWriteProcessMemory` and contains
the following functions:
- `:bool(value)`
- `:char(value)`
- `:double(value)`
- `:float(value)`
- `:int8(value)`
- `:int16(value)`
- `:int32(value)`
- `:int64(value)`
- `:intptr(value)`
- `:uint8(value)`
- `:uint16(value)`
- `:uint32(value)`
- `:uint64(value)`
- `:uintptr(value)`

## Process.findPattern(image|imageName, pattern, mask[, extraOffset][, dereferenceOnce][, subBase][, addressOffset])
Find an opcode based pattern inside a specified `image`.
- `image` (*userdata*) or `imageName` (*string*)
  - *userdata* -> an object from `Process.getImage()`
  - *string* -> the name of the image
- `pattern` (*string*) - the opcode pattern (example: `\xE8\x00\x00\x00\x00\xC4\x40`)
- `mask` (*string*) - the opcode mask (example: `x????xx`)
- `extraOffset` (*integer*, **optional**) - the opcode offset
- `dereferenceOnce` (*bool*, **optional**) - read-out (dereference) the pattern result
- `subBase`(*bool*, **optional**) - if `true` subtract the image base address from the pattern result
- `addressOffset` (*integer*, **optional**) - the pattern result offset

**Return:** the pattern result as `uintptr` or `nil`.

## Process.findSignature(image|imageName, signature[, subBase][, addressOffset])
Find an opcode based opcode-signature inside a specified `image`.
- `image` (*userdata*) or `imageName` (*string*)
  - *userdata* -> an object from `Process.getImage()`
  - *string* -> the name of the image
- `signature` (*string*) - the opcode-signature (example: `E8 ? ? ? ? C4 40`)
- `extraOffset` (*integer*, **optional**) - the opcode-signature offset
- `dereferenceOnce` (*bool*, **optional**) - read-out (dereference) the pattern result
- `subBase`(*bool*, **optional**) - if `true` subtract the image base address from the pattern result
- `addressOffset` (*integer*, **optional**) - the pattern result offset

**Return:** the pattern result as `uintptr` or `nil`.
___
## Image:getName()
Get the name of the image.

**Return:** the name as `string`.

## Image:getPath()
Get the path of the image where it's located at.

**Return:** the path as `string`.

## Image:getBase()
Get the base address of the image.

**Return:** the base address of the image as `uintptr`.

## Image:getSize()
Get the size of the image.

**Return:** the image size as `uintptr`.
