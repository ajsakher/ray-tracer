#include <ray-tracer/environment-sim/Projectile.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace EnvironmentSim {

void Projectile::increment_position(const double time) {
    this->position += this->velocity * time;
}

void Projectile::set_velocity(const Spatial::Vector& v) {
    this->velocity = v;
}

}
}
