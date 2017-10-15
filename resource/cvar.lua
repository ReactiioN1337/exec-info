--[[--------------------------------------------------------------------------------
-- Script: cvar.lua
-- Author: ReactiioN
--------------------------------------------------------------------------------]]--
CVar = {}
CVar.current = nil
CVar.list    = {}
CVar.binds   = {}

function CVar.setCurrentConfig(name)
  if type(name) == 'string' then
    CVar.current = name
  end
end

function CVar.setConfigVar(config, var, value)
  if type(config) == 'string' and type(var) == 'string' then
    if type(CVar.list[config]) ~= 'table' then
      CVar.list[config] = {}
    end
    CVar.list[config][var] = value
  end
end

function CVar.getConfigVar(config, var)
  if type(config) == 'string' and type(var) == 'string' then
    if type(CVar.list[config]) == 'table' then
      return CVar.list[config][var]
    end
  end
  return nil
end

function CVar.addConfigBind(config, name, key, clicked, callback)
  if type(config) == 'string' and type(name) == 'string' and type(callback) == 'function' then
    if type(key) == 'number' or type(key) == 'string' then
      if type(CVar.binds[config]) ~= 'table' then
        CVar.binds[config] = {}
      end
      CVar.binds[config][name] = {key, clicked, callback}
    end
  end
end

function CVar.removeConfigBind(config, name)
  if type(config) == 'string' and type(name) == 'string' then
    if type(CVar.binds[config]) == 'table' then
      CVar.binds[config][name] = nil
    end
  end
end

function CVar.runConfigBinds(config)
  if type(config) == 'string' then
    if type(CVar.binds[config]) == 'table' then
      for bindName,bindTable in pairs(CVar.binds[config]) do
        if bindTable[2] == true then
          if WinAPI.isKeyClicked(bindTable[1]) then
            bindTable[3]()
          end
        else
          local down = WinAPI.isKeyDown(bindTable[1])
          bindTable[3](down)
        end
      end
    end
  end
end

function CVar.setVar(name, value)
  CVar.setConfigVar(CVar.current, name, value)
end

function CVar.getVar(name)
  return CVar.getConfigVar(CVar.current, name)
end

function CVar.addBind(name, key, clicked, callback)
  CVar.addConfigBind(CVar.current, name, key, clicked, callback)
end

function CVar.removeBind(name)
  CVar.removeConfigBind(CVar.current, name)
end

function CVar.runBinds()
  CVar.runConfigBinds(CVar.current)
end
