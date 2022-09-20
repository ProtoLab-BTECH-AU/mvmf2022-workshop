local ReplicatedStorage = game:GetService("ReplicatedStorage")          -- Get the replicated storage service
local shakeEvent = ReplicatedStorage:WaitForChild("ShakeEvent")         -- Get the shake start event from the replicated storage
local shakeStopEvent = ReplicatedStorage:WaitForChild("ShakeStopEvent") -- Get the shake stop event from the replicated storage

local Character = script.Parent                     -- Get the player character
local Humanoid = Character:WaitForChild("Humanoid") -- Get the object representing the character
shake = false                                       -- Set a global variable to control the shaking

function onShakeEvent (Time)                                       -- Event handler to start the shaking
	shake = true                                                     -- Set the global shake variable to true
	while shake do                                                   -- While shake is true, shake the camera
		wait()                                                         -- Wait a "tick" between camera shakes
		local xOffset = math.random(-100, 100) / 500                   -- Generate a random X offset
		local yOffset = math.random(-100, 100) / 500                   -- Generate a random Y offset
		local zOffset = math.random(-100, 100) / 500                   -- Generate a random Z offset
		Humanoid.CameraOffset = Vector3.new(xOffset, yOffset, zOffset) -- Apply the offsets to the camera
	end
end

function onShakeStopEvent ()                   -- Event handler
	shake = false                                -- Set the global shake variable to false to stop the shaking in onShakeEvent
	Humanoid.CameraOffset = Vector3.new(0, 0, 0) -- Reset the camera to its starting position
end

shakeEvent.OnClientEvent:Connect(onShakeEvent)         -- When the shake start event is triggered, run onShakeEvent
shakeStopEvent.OnClientEvent:Connect(onShakeStopEvent) -- When the shake stop event is triggered, run onShakeStopEvent
