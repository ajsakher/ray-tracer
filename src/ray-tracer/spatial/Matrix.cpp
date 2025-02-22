#include <iostream>
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

Matrix get_submatrix(const Matrix& m, size_t row_remove, size_t col_remove) {
    if (row_remove >= m.get_height() || col_remove >= m.get_width()) {
        std::stringstream error;
        error << "Submatrix row_remove or column_remove out of bounds:\n";
        error << "Matrix: (" << m.get_height() << ", " << m.get_width() << ")\n";
        error << "row_remove: " << row_remove << ", col_remove: " << col_remove << "\n";
        throw std::invalid_argument(error.str());
    }
    Matrix submatrix(m.get_height() - 1, m.get_width() - 1);
    int x = 0, y = 0;
    for (int i = 0; i < m.get_height(); ++i) {
        if (i == row_remove) continue;
        y = 0;
        for (int j = 0; j < m.get_width(); ++j) {
            if (j == col_remove) continue;
            submatrix(x, y) = m(i, j);
            ++y;
        }
        ++x;
    }
    return submatrix;
}

double minor(const Matrix& m, size_t row_remove, size_t col_remove) {
    return get_submatrix(m, row_remove, col_remove).determinant();
}

double cofactor(const Matrix& m, size_t row_remove, size_t col_remove) {
    return (row_remove + col_remove) % 2 == 0 ?
        minor(m, row_remove, col_remove) :
        -minor(m, row_remove, col_remove);
}

double Matrix::determinant() const {
    if (this->width != this->height) {
        std::stringstream error;
        error << "Determinant does not exist for non-square matrix of size: ";
        error << "(" << this->height << ", " << this->width << ")\n";
        throw std::runtime_error(error.str());
    }
    const Matrix& m = *this;
    if (this->width == 2) {
        return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
    }
    double total = 0;
    for (int i = 0; i < this->width; ++i) {
        total += m(0, i) * cofactor(m, 0, i);
    }
    return total;
}

Matrix Matrix::invert() const {
    double det = this->determinant();
    if (det == 0) {
        throw std::runtime_error(
            "Matrix with determinant of 0 is not invertible");
    }
    Matrix inverted(this->height, this->width);
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            inverted(j, i) = cofactor(*this, i, j) / det;
        }
    }
    return inverted;
}

void print_matrix(const Matrix& m) {
    for (int i = 0; i < m.get_height(); ++i) {
        for (int j = 0; j < m.get_width(); ++j) {
            std::cout << m(i, j);
            if (j != m.get_width() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

}
}
