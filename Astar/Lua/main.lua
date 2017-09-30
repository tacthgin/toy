local astar = require "astar"

local map = {
	{0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 0},
	{0, 0, 1, 0, 1, 0},
	{0, 1, 1, 0, 1, 0},
	{0, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0}
}

function printMap()
	for i=1, #map do
		local s = ""
		for j=1, #map[i] do
			s = s..string.format("%d ", map[i][j])
		end
		print(s)
	end
end

function main()
	local path = astar:getPath({x = 1, y = 1}, {x = 3, y = 4}, map)

	if path ~= nil then
		print("before")
		printMap()
		
		local n = nil
		for i=1, #path do
			n = path[i]
			map[n:get_pos().x][n:get_pos().y] = 2
		end

		print("after")
		printMap()
	end
end

main()
