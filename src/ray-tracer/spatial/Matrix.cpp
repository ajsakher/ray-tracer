#include <sstream>
#include <stdexcept>
#include <vector>

#include <ray-tracer/core/util.hpp>
#include <ray-tracer/spatial/Matrix.hpp>

namespace RayTracer {
namespace Spatial {

Matrix Matrix::get_identity(size_t n) {
    Matrix identity(n, n);
    for (int i = 0; i < n; ++i) {
        identity(i, i) = 1;
    }
    return identity;
}

Matrix::Matrix(size_t h, size_t w) : height(h), width(w) {
    if (width == 0 || height == 0) {
        throw std::invalid_argument("Invalid width or height when creating matrix.");
    }
    values = std::vector<double>(width * height, 0);
}

Matrix::Matrix(const std::vector< std::vector<double> >& init) {
    if (init.size() == 0 || init[0].size() == 0) {
        throw std::invalid_argument("Invalid width or height when creating matrix.");
    }
    height = init.size();
    width = init[0].size();
    values = std::vector<double>(width * height, 0);
    for (int i = 0; i < init.size(); ++i) {
        for (int j = 0; j < init[0].size(); ++j) {
            if (init[0].size() != init[i].size()) {
                throw std::invalid_argument("Matrix initialization rows are different lengths, invalid");
            }
            (*this)(i, j) = init[i][j];
        }
    }
}

void Matrix::check_bounds(size_t x, size_t y) const {
    if (x < 0 || y < 0 || x >= height || y >= width) {
        std::stringstream error;
        error << "Invalid x or y when accessing matrix value: (";
        error << x << ", " << y << ") for matrix with dimensions: (";
        error << this->height << ", " << this->width << ")\n";
        throw std::invalid_argument(error.str());
    }
}

double& Matrix::operator()(size_t x, size_t y) {
    check_bounds(x, y);
    return this->values[width * x + y];
}

const double& Matrix::operator()(size_t x, size_t y) const {
    check_bounds(x, y);
    return this->values[width * x + y];
}

bool Matrix::operator==(const Matrix& b) const {
    if (this->width != b.width || this->height != b.height) {
        return false;
    }
    for (int i = 0; i < width * height; ++i) {
        if (!Core::essentially_equal(this->values[i], b.values[i])) {
            return false;
        }
    }
    return true;
}

Matrix Matrix::operator*(const Matrix& b) const {
    if (this->width != b.height) {
        throw std::invalid_argument("Invalid matrix multiplication dimensions.");
    }
    Matrix result(this->height, b.width);
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < b.width; ++j) {
            double next_value = 0;
            for (int k = 0; k < b.height; ++k) {
                next_value += (*this)(i, k) * b(k, j);

            }
            result(i, j) = next_value;
        }
    }
    return result;
}

Point Matrix::operator*(const Point& p) const {
    if (this->width != 4 || this->height != 4) {
        throw std::invalid_argument(
            "Support only for 4x4 matrix multiplication for points");
    }
    std::vector<double> vals(3, 0);
    for (int i = 0; i < 3; ++i) {
        double sum = (*this)(i, 0) * p.get_x() +
            (*this)(i, 1) * p.get_y() +
            (*this)(i, 2) * p.get_z() +
            (*this)(i, 3) * p.get_w();
        vals[i] = sum;
    }
    return Point(vals[0], vals[1], vals[2]);
}

Vector Matrix::operator*(const Vector& p) const {
    if (this->width != 4 || this->height != 4) {
        throw std::invalid_argument(
            "Support only for 4x4 matrix multiplication for vectors");
    }
    std::vector<double> vals(3, 0);
    for (int i = 0; i < 3; ++i) {
        double sum = (*this)(i, 0) * p.get_x() +
            (*this)(i, 1) * p.get_y() +
            (*this)(i, 2) * p.get_z() +
            (*this)(i, 3) * p.get_w();
        vals[i] = sum;
    }
    return Vector(vals[0], vals[1], vals[2]);
}

Matrix Matrix::transpose() const {
    Matrix new_matrix(this->width, this->height);
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            new_matrix(j, i) = (*this)(i, j);
        }
    }
    return new_matrix;
}

}
}
