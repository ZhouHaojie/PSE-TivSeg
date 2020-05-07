#pragma once

struct SDL_Surface;

/// RGB Color
class Color
{
public:
	/// Default constructor (black).
	Color() : Color(0, 0, 0)
	{
	}

	/// Parametrized constructor.
	Color(unsigned char r, unsigned char g, unsigned char b) :
			m_R(r), m_G(g), m_B(b)
	{
	}

	/// Get red component.
	unsigned char r() const
	{
		return m_R;
	}

	/// Get green component.
	unsigned char g() const
	{
		return m_G;
	}

	/// Get blue component.
	unsigned char b() const
	{
		return m_B;
	}

private:
	unsigned char m_R, m_G, m_B;
};

/// Helper class to track and draw bounding boxes on screen.
class BoundingBox
{
public:
	/// Default constructor (empty box).
	BoundingBox();
	/// Parametrized constructor.
	BoundingBox(int x, int y, int width, int height, int regionID);

	/// Expand this box to also bound the other box.
	void join(const BoundingBox& other);

	/// Check if this box overlaps the other box.
	bool isOverlapping(const BoundingBox& other) const;

	/// Get x (left) coordinate.
	int x() const { return m_X; }

	/// Get y (top) coordinate.
	int y() const { return m_Y; }

	/// Get width.
	int getWidth() const { return m_Width; }

	/// Get height.
	int getHeight() const { return m_Height; }

	/// Get area.
	int getArea() const;

	/// Get region id.
	int getRegionID() const { return m_RegionID; }

	/// Grow this box around its center.
	void grow(int amount);

	/// Draw this box onto an SDL surface.
	void draw(struct SDL_Surface* surface);

	/// Draw a marker onto an SDL surface.
	void drawMarker(struct SDL_Surface* surface);

	/// Set outline color.
	void setPen(Color color) { m_PenColor = color; }

	static bool xLt(const BoundingBox& first, const BoundingBox& second) { return (first.x() < second.x()); }
	static bool yLt(const BoundingBox& first, const BoundingBox& second) { return (first.y() < second.y()); }
	static bool areaLt(const BoundingBox& first, const BoundingBox& second) { return (first.getArea() < second.getArea()); }

protected:
	int m_X, m_Y;
	int m_Width, m_Height;
	int m_RegionID;

	Color m_PenColor;

	bool m_IsEmpty;
};
