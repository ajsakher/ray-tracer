#pragma once

#include <cmath>
#include <fstream>
#include <string>

namespace RayTracer {
namespace Core {

bool write_file(const std::string& file_content, const std::string& filename);

bool essentially_equal(double a, double b, double epsilon);
bool essentially_equal(double a, double b);

}
}
