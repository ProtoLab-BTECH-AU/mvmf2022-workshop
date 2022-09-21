local ReplicatedStorage = game:GetService("ReplicatedStorage") -- Get the replicated storage service
local HttpService = game:GetService("HttpService")             -- Get the HTTP service

local shakeEvent = ReplicatedStorage:WaitForChild("ShakeEvent")         -- Get the shake start event from the replicated storage
local shakeStopEvent = ReplicatedStorage:WaitForChild("ShakeStopEvent") -- Get the shake stop event from the replicated storage

local product = "16909"                                  -- This is the ID of the "product" the particle device belongs to
local device = "e00fce68c0fae090f645d06f"                -- This is the ID of the particle device
local token = "3337902341d2ed9551ed753a0f08bcf33c0dcdca" -- This is the user's personal token
local url = string.format("https://api.particle.io/v1/products/%s/devices/%s/wasTapped?access_token=%s", product, device, token)

function loop ()
	while (true) do                                    -- Do forever
		local response = HttpService:GetAsync(url, true) -- Send a GET request to the API endpoint
		local data = HttpService:JSONDecode(response)     -- Get the JSON values from the response
		print(string.format("shake: %d", data.result))   -- Print the result in the console log
		if (data.result > 0) then                        -- If the result is positive (i.e. the device was shaken) trigger the shake start event for all clients
			shakeEvent:FireAllClients()
		else                                             -- If the result is 0 (i.e. the device was not shaken in the reset interval) trigger the shake stop event for all clients
			shakeStopEvent:FireAllClients()
		end
		wait(2)                                          -- Wait 2 seconds before sending a new request
	end
end

while (true) do
	if not pcall(loop) then
		print("shake: an error occurred")
	end
	wait(5)
end
