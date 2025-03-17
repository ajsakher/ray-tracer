#include <ray-tracer/ray-cast/Ray.hpp>
#include <ray-tracer/spatial/Matrix.hpp>
#include <ray-tracer/spatial/Point.hpp>

namespace RayTracer {
namespace RayCast {

Spatial::Point position(const Ray& r, const double t) {
    return r.get_origin() + (r.get_direction() * t);
}

Ray transform(const Ray& r, const Spatial::Matrix& transformation) {
    return Ray(
        transformation * r.get_origin(),
        transformation * r.get_direction()
    );
}

}
}
