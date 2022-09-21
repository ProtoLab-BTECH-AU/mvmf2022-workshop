local ReplicatedStorage = game:GetService("ReplicatedStorage") -- Get the replicated storage service
local HttpService = game:GetService("HttpService")             -- Get the HTTP service

local lightEvent = ReplicatedStorage:WaitForChild("LightEvent") -- Get the light event from the replicated storage

local product = "16909"                                  -- This is the ID of the "product" the particle device belongs to
local device = "e00fce68c0fae090f645d06f"                -- This is the ID of the particle device
local token = "3337902341d2ed9551ed753a0f08bcf33c0dcdca" -- This is the user's personal token
local url = string.format("https://api.particle.io/v1/products/%s/devices/%s/light?access_token=%s", product, device, token)

function loop ()
	while (true) do                                    -- Do forever
		local response = HttpService:GetAsync(url, true) -- Send a GET request to the API endpoint
		local data = HttpService:JSONDecode(response)    -- Get the JSON values from the response
		print(string.format("light: %f", data.result))   -- Print the result in the console log
		lightEvent:FireAllClients(data.result)           -- Trigger the event for all clients using the result field of the JSON response
		wait(5)                                          -- Wait 5 seconds before sending a new request
	end
end

while (true) do
	local _, err = pcall(loop)
	if err then
		print(string.format("light: error: %s", err))
	end
	wait(5)
end
