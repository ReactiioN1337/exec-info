## Timer.new(duration)
Creates a new table and copies the contents from `Timer` to it.
You have to call this function whenever you need a **new** Timer!

* `duration` - `number` the duration in milliseconds.

**return:** a new Timer as `table`.

## Timer:run()
Runs the timer tick, calculates if is finished and the percentage.

**return:** a `boolean` which is `true` if the timer has reached the duration, `false` otherwise.

## Timer:getPercentage()
Get the current percentage.

**return:** a `number` which can be `0`, `1` or anyone between them.

## Timer:setDuration(duration)
Sets the timer duration in milliseconds.

* `duration` - `number` the duration in milliseconds.

## Timer:reset()
Reset the timer data.
