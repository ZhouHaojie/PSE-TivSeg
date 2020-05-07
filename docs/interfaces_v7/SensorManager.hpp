#pragma once

#include <vector>
#include <memory>
#include <SDL/SDL.h>

#include <MarkerInfo.hpp>

class SensorManagerPimpl;
struct SDL_Surface;

/// Sensor and image processing manager.
class SensorManager
{
public:
	SensorManager(const SensorManager&) = delete;
	SensorManager& operator=(const SensorManager&) = delete;

	/// Get the singleton instance of the sensor manager.
	static SensorManager* getInstance();

	/// Update color and depth data, and perform marker detection.
	bool runOnce();

	/// Get the list of currently detected markers.
	std::vector<MarkerInfo> getMarkerList();

	/// Get the width of the sensor data.
	int getSensorWidth();

	/// Get the height of the sensor data.
	int getSensorHeight();

	/// Get the depth [m] at the given pixel in the sensor data.
	double getDepth(int x, int y);

	/// Get an average of the current processing FPS
	float getFps();

	/// Get the surface for drawing debug information. This will by default already show the camera image.
	struct SDL_Surface* getDebugDisplaySurface();

protected:
	SensorManager();
	~SensorManager();

	std::shared_ptr<SensorManagerPimpl> m_Pimpl;
};
