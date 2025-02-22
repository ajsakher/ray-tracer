#include <ray-tracer/examples/environment-sim/Environment.hpp>
#include <ray-tracer/examples/environment-sim/EnvironmentSim.hpp>
#include <ray-tracer/examples/environment-sim/Projectile.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace EnvironmentSim {

Projectile tick(const Environment& e, const Projectile& p) {
    return Projectile(
        Spatial::Point(p.get_position() + p.get_velocity()),
        Spatial::Vector(p.get_velocity() + e.get_gravity() + e.get_wind())
    );
}

}
}

