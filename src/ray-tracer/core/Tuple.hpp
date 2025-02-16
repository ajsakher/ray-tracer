#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H

#include <memory>
#include <vector>

namespace RayTracer {
namespace Core {

class Tuple {
protected:
    std::vector<double> values;
public:
    const std::vector<double>& get_values() { return this->values; }
};

}
}

#endif //RAYTRACER_TUPLE_H
