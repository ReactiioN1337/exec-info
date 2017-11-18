Matrix         = {}
Matrix.numRows = 0
Matrix.numCols = 0

function Matrix.new(rows, cols)
  if type(rows) ~= 'number' or type(cols) ~= 'number' then
    return nil
  end
  if rows <= 0 or cols <= 0 then
    return nil
  end

  local obj = deepcopy(Matrix)
  for i = 1, rows * cols do
    obj[i] = 0
  end

  obj.numRows = rows
  obj.numCols = cols

  return obj
end

function Matrix:isVector()
  if self then
    return self.numRows == 1 or self.numCols == 1
  end
  return false
end

function Matrix:at(row, col)
  if self then
    return self[math.min((row - 1), 0) * self.numCols + col]
  end
  return nil
end

function Matrix:getRow(rowIndex)
  if self then
    local obj = Matrix.new(1, self.numCols)
    for i = 1, self.numCols do
      obj[i] = self:at(rowIndex, i)
    end
    return obj
  end
  return nil
end

function Matrix:getCol(colIndex)
  if self then
    local obj = Matrix.new(self.numRows, 1)
    for i = 1, self.numRows do
      obj[i] = self:at(i, colIndex)
    end
    return obj
  end
  return nil
end

function Matrix:size()
  if self then
    return self.numRows * self.numCols
  end
  return nil
end

function Matrix:distance(rhs)
  if self then
    if self:isVector() and rhs:isVector() then
      local obj = deepcopy(rhs)
      for i = 1, math.min(self:size(), rhs:size()) do
        obj[i] = obj[i] - self[i]
      end
      return obj:norm()
    end
  end
  return nil
end

function Matrix:dot(rhs)
  if self then
    if self:isVector() and rhs:isVector() then
      local buf = 0
      for i = 1, math.min(self:size(), rhs:size()) do
        buf = buf + self[i] * rhs[i]
      end
      return buf
    end
  end
  return nil
end

function Matrix:cross(rhs)
  if self then
    if self:size() == 3 and rhs:size() == 3 then
      local obj = Matrix.new(self.numRows, self.numCols)
      obj[1] = self[2] * rhs[3] - self[3] * rhs[2]
      obj[2] = self[3] * rhs[1] - self[1] * rhs[3]
      obj[3] = self[1] * rhs[2] - self[2] * rhs[1]
      return obj
    end
  end
  return nil
end

function Matrix:ncross(rhs)
  if self then
    local obj = self:cross(rhs)
    if obj ~= nil then
      obj:normalize()
      return obj
    end
  end
  return nil
end

function Matrix:normsqr()
  if self then
    if self:isVector() then
      local x = 0
      for i = 1, self:size() do
        x = x + self[i] * self[i]
      end
      return x
    end
  end
  return nil
end

function Matrix:norm()
  if self then
    local sqr = self:normsqr()
    if sqr ~= nil then
      return math.sqrt(sqr)
    end
  end
  return nil
end

function Matrix:normalize()
  if self then
    local length = self:norm()
    if length ~= nil then
      for i = 1, self:size() do
        self[i] = self[i] / length
      end
    end
  end
end

function Matrix:normalized()
  if self then
    local buf = deepcopy(self)
    buf:normalize()
    return buf
  end
  return nil
end

function Matrix:inversed()
  if self then
    local obj = deepcopy(self)
    for i = 1, self:size() do
      obj[i] = 1 / obj[i]
    end
    return obj
  end
  return nil
end

function Matrix:fill(value)
  if self and type(value) == 'number' then
    for i = 1, self:size() do
      self[i] = value
    end
    return self
  end
  return nil
end

function Matrix:clamp(index, mins, maxs)
  if self then
    if self[index] ~= nil then
      self[index] = math.clamp(self[index], mins, maxs)
    end
  end
end

function Matrix:readFromMemory(address)
  if not self or not Process or address <= 0 then
    return false
  end
  for i = 1, self:size() do
    self[i] = Process.read(address + ((i - 1) * 0x4)):float()
  end
  return true
end

function Matrix:writeToMemory(address)
  if not self or not Process or address <= 0 then
    return false
  end
  for i = 1, self:size() do
    Process.write(address + ((i - 1) * 0x4)):float(self[i])()
  end
  return true
end

setmetatable(Matrix, {
  __add = function(lhs, rhs)
    if not lhs or not rhs then return nil end

    local obj   = deepcopy(lhs)
    local isNum = type(rhs) == 'number'

    if not isNum and lhs:size() ~= rhs.size() then
      return nil
    end

    for i = 1, obj:size() do
      if isNum then
        obj[i] = obj[i] + rhs
      else
        obj[i] = obj[i] + rhs[i]
      end
    end

    return obj
  end,

  __sub = function(lhs, rhs)
    if not lhs or not rhs then return nil end

    local obj   = deepcopy(lhs)
    local isNum = type(rhs) == 'number'

    if not isNum and lhs:size() ~= rhs.size() then
      return nil
    end

    for i = 1, obj:size() do
      if isNum then
        obj[i] = obj[i] - rhs
      else
        obj[i] = obj[i] - rhs[i]
      end
    end

    return obj
  end,

  __mul = function(lhs, rhs)
    if not lhs or not rhs then return nil end

    local obj   = deepcopy(lhs)
    local isNum = type(rhs) == 'number'

    if not isNum and lhs:size() ~= rhs.size() then
      return nil
    end

    for i = 1, obj:size() do
      if isNum then
        obj[i] = obj[i] * rhs
      else
        obj[i] = obj[i] * rhs[i]
      end
    end

    return obj
  end,

  __div = function(lhs, rhs)
    if not lhs or not rhs then return nil end

    local obj   = deepcopy(lhs)
    local isNum = type(rhs) == 'number'

    if not isNum and lhs:size() ~= rhs.size() then
      return nil
    end

    for i = 1, obj:size() do
      if isNum then
        obj[i] = obj[i] / rhs
      else
        obj[i] = obj[i] / rhs[i]
      end
    end

    return obj
  end
})
