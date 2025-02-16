#include <cmath>
#include <fstream>
#include <string>

#include <ray-tracer/core/util.hpp>

namespace RayTracer {
namespace Core {

bool write_file(const std::string& file_content, const std::string& filename) {
    std::ofstream out_file(filename);
    if (out_file.is_open()) {
        out_file << file_content;
        out_file.close();
        return true;
    }
    return false;
}

const double DEFAULT_EPSILON = 0.00001;

bool essentially_equal(double a, double b, double epsilon) {
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool essentially_equal(double a, double b) {
    return essentially_equal(a, b, DEFAULT_EPSILON);
}

}
}
