--[[--------------------------------------------------------------------------------
-- Script: timer.lua
-- Author: ReactiioN
--------------------------------------------------------------------------------]]--
Timer = {}
Timer.startTime  = nil
Timer.finished   = false
Timer.duration   = nil
Timer.percentage = 0

function Timer.new(duration)
  local timer = deepcopy(Timer)
  if type(duration) == 'number' then
    timer:setDuration(duration)
  end
  return timer
end

function Timer:run()
  if self.finished then
    return true
  end

  if self.startTime == nil then
    self.startTime = os.clock()
  end

  local delta = os.clock() - self.startTime
  self.percentage = 1 / self.duration * delta
  
  if self.percentage > 1 then
    self.percentage = 1
  end

  if delta > self.duration then
    self.finished = true
  end

  return self.finished
end

function Timer:getPercentage()
  return self.percentage
end

function Timer:setDuration(duration)
  if type(duration) == 'number' then
    self.duration = duration / 1000
  end
end

function Timer:reset()
  self.startTime = nil
  self.finished  = false
end
