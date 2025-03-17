#pragma once

#include <ray-tracer/display/Color.hpp>
#include <ray-tracer/spatial/Point.hpp>

namespace RayTracer {
namespace Display {

class PointLight {
private:
    Spatial::Point position;
    Color intensity;
public:
    PointLight(const Spatial::Point& p, const Color& i) : position(p), intensity(i) {}
    const Spatial::Point& get_position() const { return position; }
    const Color& get_intensity() const { return intensity; }
};

}
}
