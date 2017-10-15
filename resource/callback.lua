--[[--------------------------------------------------------------------------------
-- Script: callback.lua
-- Author: ReactiioN
--------------------------------------------------------------------------------]]--
Callback = {}
Callback.list = {}

function Callback.add(groupName, name, callback)
  if type(Callback.list[groupName]) ~= 'table' then
    Callback.list[groupName] = {}
  end
  Callback.list[groupName][name] = callback
end

function Callback.remove(groupName, name)
  if type(Callback.list[groupName]) == 'table' then
    Callback.list[groupName][name] = nil
  end
end

function Callback.removeGroup(groupName)
  if type(Callback.list[groupName]) == 'table' then
    Callback.list[groupName] = nil
  end
end

function Callback.exec(groupName, arg)
  if type(Callback.list[groupName]) == 'table' then
    for _,callback in pairs(Callback.list[groupName]) do
      if type(callback) == 'function' then
        callback(arg)
      end
    end
  end
end
