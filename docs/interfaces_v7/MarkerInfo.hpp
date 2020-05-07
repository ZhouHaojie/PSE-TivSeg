#pragma once

#include <BoundingBox.hpp>

/// Information about detected marker
struct MarkerInfo
{
	/// bounding box of the marker
	BoundingBox m_Marker;

	/// Detection confidence. Range is 0 to 100; 0 is worst, 100 is best.
	int m_Confidence;
};
