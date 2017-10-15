--[[--------------------------------------------------------------------------------
-- Script: autoclicker.lua
-- Author: ReactiioN
--------------------------------------------------------------------------------]]--
CVar.setCurrentConfig('default')

CVar.addBind('increase', 'mouse5', false, function(down)
  if not down then
    return
  end

  WinAPI.emulateMouseClick( true, 3, 1 )
end)

CVar.addBind('decrease', 'mouse4', false, function(down)
  if not down then
    return
  end

  WinAPI.emulateMouseClick( false, 3, 1 )
end)

function onScriptTick()
  CVar.runBinds()
end

function WinAPI.emulateMouseClick(left, delay, delayAfter)
  local downFlags, upFlags

  if left == true then
    downFlags = MOUSEEVENTF_LEFTDOWN
    upFlags   = MOUSEEVENTF_LEFTUP
  else
    downFlags = MOUSEEVENTF_RIGHTDOWN
    upFlags   = MOUSEEVENTF_RIGHTUP
  end

  WinAPI.mouseEvent( downFlags, 0, 0, 0, 0 )
  if type(delay) == 'number' then
    WinAPI.sleep( delay )
  end

  WinAPI.mouseEvent( upFlags, 0, 0, 0, 0 )
  if type(delayAfter) == 'number' then
    WinAPI.sleep( delayAfter )
  end
end
