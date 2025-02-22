#ifndef RAYTRACER_ENVIRONMENTSIM_PROJECTILE_HPP
#define RAYTRACER_ENVIRONMENTSIM_PROJECTILE_HPP

#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace EnvironmentSim {

class Projectile {
private:
    Spatial::Point position;
    Spatial::Vector velocity;
public:
    Projectile(const Spatial::Point& p, const Spatial::Vector& v) :
        position(p), velocity(v) {}
    Projectile() :
        position(Spatial::Point(0, 0, 0)),
        velocity(Spatial::Vector(0, 0, 0)) {}
    void increment_position(const double time = 1);
    void set_velocity(const Spatial::Vector&);

    const Spatial::Point& get_position() const {
        return position;
    }

    const Spatial::Vector& get_velocity() const {
        return velocity;
    }
};

}
}

#endif
