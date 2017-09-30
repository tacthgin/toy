--A*--
local node = {}
node.__index = node
function node.new(pos, h, p)
	local n = {}
	n.pos = {x = pos.x, y = pos.y}
	n.h = h
	n.parent = p
	n.g = 0
	if p ~= nil then
		n.g = p.g + 1
	end
	n.f = n.g + n.h
	return setmetatable(n, node)
end

function node:get_pos()
	return self.pos
end

function node:get_g()
	return self.g
end

function node:get_f()
	return self.f
end

local astar = {}
astar.close = {}
astar.open = {}

local abs = math.abs
local function estimate_hvalue(srcPos, dstPos)
	return abs(srcPos.x - dstPos.x) + abs(srcPos.y - dstPos.y);
end

local function nodeSort(l, r)
	if l:get_f() == r:get_f() then
		return l:get_g() > r:get_g()
	end

	return l:get_f() < r:get_f()
end

local function contain(t, pos)
	for _, v in ipairs(t) do
		if v:get_pos().x == pos.x and v:get_pos().y == pos.y then
			return v
		end
	end
end

function astar:fitNode(pos)
	if self.map[pos.x] ~= nil and self.map[pos.x][pos.y] == 0 then
		return true
	end
	return false
end

function astar:addOtherNode(curNode)
	if curNode == nil then return end

	local d = {
		{x = 0, y = 1},
		{x = 0, y = -1},
		{x = -1, y =  0},
		{x = 1, y = 0}
	}

	table.insert(self.close, curNode)

	local newPos, h = {x = 0, y = 0}, 0
	for _, v in ipairs(d) do
		newPos.x = curNode:get_pos().x + v.x
		newPos.y = curNode:get_pos().y + v.y
		h = estimate_hvalue(newPos, self.dstPos)
		if contain(self.close, newPos) == nil and self:fitNode(newPos) then
			table.insert(self.open, node.new(newPos, h, curNode))
		end
	end
	
	table.sort(self.open, nodeSort)
end

function astar:makePath()
	self.close = {}
	self.open = {}
	local path = {}

	local h = estimate_hvalue(self.srcPos, self.dstPos)
	if h == 0 then return end

	local n = node.new(self.srcPos, h, nil)
	table.insert(self.open, n)

	local last = nil
	while #self.open ~= 0 and last == nil do
		n = table.remove(self.open, 1)
		self:addOtherNode(n)
		last = contain(self.open, self.dstPos)
	end

	while last ~= nil do
		table.insert(path, 1, last)
		last = last.parent
	end

	return path
end

function astar:getPath(sPos, dPos, map)
	self.srcPos = {x = sPos.x, y = sPos.y}
	self.dstPos = {x = dPos.x, y = dPos.y}
	self.map = map

	if map ~= nil and self:fitNode(self.srcPos) and self:fitNode(self.dstPos) then
		return self:makePath()
	end
end

return astar