#pragma once

#include <ray-tracer/display/Color.hpp>
#include <ray-tracer/display/Material.hpp>
#include <ray-tracer/display/PointLight.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Display {

Color lighting(
    const Material&,
    const PointLight&,
    const Spatial::Point&,
    const Spatial::Vector&,
    const Spatial::Vector&
);

}
} // namespace RayTracer
