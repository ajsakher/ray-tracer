#pragma once

#include <stdexcept>
#include <type_traits>
#include <vector>

#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace Spatial {

class Matrix {
private:
    std::vector<double> values;
    size_t width;
    size_t height;
    void check_bounds(size_t, size_t) const;
public:
    static Matrix get_identity(size_t);

    Matrix(size_t, size_t);
    Matrix(const std::vector< std::vector<double> >&);

    const size_t get_width() const { return width; }
    const size_t get_height() const { return height; }

    double& operator()(size_t, size_t);
    const double& operator()(size_t, size_t) const;

    bool operator==(const Matrix&) const;

    Matrix operator*(const Matrix&) const;
    Point operator*(const Point&) const;
    Vector operator*(const Vector&) const;

    Matrix transpose() const;
    Matrix invert() const;

    double determinant() const;
};

Matrix get_submatrix(const Matrix&, size_t, size_t);
double minor(const Matrix&, size_t, size_t);
double cofactor(const Matrix&, size_t, size_t);

void print_matrix(const Matrix&);

}
}
