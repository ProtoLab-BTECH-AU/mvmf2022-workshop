local ReplicatedStorage = game:GetService("ReplicatedStorage")  -- Get the replicated storage service
local lightEvent = ReplicatedStorage:WaitForChild("LightEvent") -- Get the light event from the replicated storage

local Lighting = game:GetService("Lighting")                    -- Get the lighting service

function onLightEvent (lightLevel)                                  -- Event handler to set the time of day
	local minutesPrev = Lighting:GetMinutesAfterMidnight()            -- Get the current time of day
	local minutesNew = math.floor((4 * 60) + ((8 * lightLevel) * 60)) -- Calculate the new time of day
	local diff = 5                                                    -- Set the amount of minutes to change the time by at every step

	minutesNew -= minutesNew % diff  -- Reduce the time to the nearest multiple of diff

	if minutesNew < minutesPrev then -- If the new time of day is earlier than the previous one, then  use a negative value for diff
		diff = -diff
	end

	print(string.format("light client: %f (%f -> %f)", lightLevel, minutesPrev, minutesNew)) -- Print the values in the console log

	while Lighting:GetMinutesAfterMidnight() ~= minutesNew do                     -- While the time of day is different than the new value, chage the time
		wait(.05)                                                                   -- Wait 50 milliseconds between steps
		Lighting:SetMinutesAfterMidnight(Lighting:GetMinutesAfterMidnight() + diff) -- Change the time of day by +/- diff
	end
end

Lighting:SetMinutesAfterMidnight(12 * 60)      -- Set the time of day to 12.00
lightEvent.OnClientEvent:Connect(onLightEvent) -- When the light event is triggered, run onLightEvent
