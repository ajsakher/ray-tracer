#include <stdexcept>

#include "gtest/gtest.h"

#include <ray-tracer/spatial/Matrix.hpp>

TEST(Matrix, invalid_initialization) {
    EXPECT_THROW(RayTracer::Spatial::Matrix m({
        { 1, 2, 3 },
        { 1, 2, 3, 4 },
    }), std::invalid_argument);
}

TEST(Matrix, constructor_invalid_dimension) {
    EXPECT_THROW(RayTracer::Spatial::Matrix m(0, 1), std::invalid_argument);
    EXPECT_THROW(RayTracer::Spatial::Matrix m(1, 0), std::invalid_argument);
}

TEST(Matrix, matrix_invalid_access) {
    RayTracer::Spatial::Matrix m(3, 5);
    EXPECT_THROW(m(10, 0), std::invalid_argument);
    EXPECT_THROW(m(0, 10), std::invalid_argument);
    EXPECT_THROW(m(-1, 0), std::invalid_argument);
    EXPECT_THROW(m(0, -1), std::invalid_argument);
}

TEST(Matrix, matrix_set_and_access_element) {
    RayTracer::Spatial::Matrix m(3, 5);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            EXPECT_EQ(m(i, j), 0);
        }
    }
    m(0, 1) = 3.5;
    m(0, 4) = 10;
    m(1, 3) = 9;
    m(2, 1) = 5;
    EXPECT_EQ(m(0, 1), 3.5);
    EXPECT_EQ(m(0, 4), 10);
    EXPECT_EQ(m(1, 3), 9);
    EXPECT_EQ(m(2, 1), 5);
}

TEST(Matrix, equivalency) {
    RayTracer::Spatial::Matrix m(3, 5);
    m(0, 1) = 3.5;
    m(0, 4) = 10;
    m(1, 3) = 9;
    m(2, 1) = 5;
    RayTracer::Spatial::Matrix m2(3, 5);
    m2(0, 1) = 3.5;
    m2(0, 4) = 10;
    m2(1, 3) = 9;
    m2(2, 1) = 20;
    EXPECT_FALSE(m == m2);
    m2(2, 1) = 5;
    EXPECT_TRUE(m == m2);
}

TEST(Matrix, multiplication) {
    RayTracer::Spatial::Matrix a({
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 8, 7, 6 },
        { 5, 4, 3, 2 }
    });
    RayTracer::Spatial::Matrix b({
        { -2, 1, 2, 3 },
        { 3, 2, 1, -1 },
        { 4, 3, 6, 5 },
        { 1, 2, 7, 8 }
    });
    RayTracer::Spatial::Matrix expected({
        { 20, 22, 50, 48 },
        { 44, 54, 114, 108 },
        { 40, 58, 110, 102 },
        { 16, 26, 46, 42 }
    });
    RayTracer::Spatial::Matrix c = a * b;
    EXPECT_EQ(c, expected);

    a = RayTracer::Spatial::Matrix({
        { 1, 2, 3 },
        { 4, 5, 6 }
    });
    b = RayTracer::Spatial::Matrix({
        { 1, 2 },
        { 4, 5 },
        { 6, 7 }
    });
    expected = RayTracer::Spatial::Matrix({
        { 27, 33 },
        { 60, 75 }
    });
    EXPECT_EQ(a * b, expected);

    a = RayTracer::Spatial::Matrix({
        { 1, 2, 3 },
    });
    b = RayTracer::Spatial::Matrix({
        { 1 },
        { 4 },
        { 6 }
    });
    expected = RayTracer::Spatial::Matrix({
        { 27 }
    });
    EXPECT_EQ(a * b, expected);

    a = RayTracer::Spatial::Matrix({
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    });
    b = RayTracer::Spatial::Matrix({
        { 1 },
        { 4 },
        { 6 }
    });
    expected = RayTracer::Spatial::Matrix({
        { 27 },
        { 60 },
        { 93 }
    });
    EXPECT_EQ(a * b, expected);

    a = RayTracer::Spatial::Matrix({
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    });
    b = RayTracer::Spatial::Matrix({
        { 1, 4, 6 },
    });
    expected = RayTracer::Spatial::Matrix({
        { 59, 70, 81 },
    });
    EXPECT_EQ(b * a, expected);

    RayTracer::Spatial::Matrix i3 = RayTracer::Spatial::Matrix::get_identity(3);
    EXPECT_EQ(a * i3, a);
    EXPECT_EQ(i3 * a, a);
}

TEST(Matrix, matrix_invalid_multiplication) {
    RayTracer::Spatial::Matrix m(3, 5);
    RayTracer::Spatial::Matrix n(3, 5);
    EXPECT_THROW(m * n, std::invalid_argument);
}

TEST(Matrix, vector_multiplication) {
    RayTracer::Spatial::Matrix m({
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    });
    RayTracer::Spatial::Vector v(1, 2, 3);
    EXPECT_EQ(m * v, RayTracer::Spatial::Vector(14, 22, 32));
}

TEST(Matrix, invalid_vector_multiplication) {
    RayTracer::Spatial::Matrix m({
        {1, 2, 3, 4, 4},
        {2, 4, 4, 2, 6},
        {8, 6, 4, 1, 8},
        {0, 0, 0, 1, 10}
    });
    RayTracer::Spatial::Vector v(1, 2, 3);
    EXPECT_THROW(m * v, std::invalid_argument);
}

TEST(Matrix, point_multiplication) {
    RayTracer::Spatial::Matrix m({
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    });
    RayTracer::Spatial::Point p(1, 2, 3);
    EXPECT_EQ(m * p, RayTracer::Spatial::Point(18, 24, 33));
}

TEST(Matrix, invalid_point_multiplication) {
    RayTracer::Spatial::Matrix m({
        {1, 2, 3, 4, 4},
        {2, 4, 4, 2, 6},
        {8, 6, 4, 1, 8},
        {0, 0, 0, 1, 10}
    });
    RayTracer::Spatial::Point p(1, 2, 3);
    EXPECT_THROW(m * p, std::invalid_argument);
}

TEST(Matrix, point_identity_multiplication) {
    RayTracer::Spatial::Point p(1, 2, 3);
    EXPECT_EQ(RayTracer::Spatial::Matrix::get_identity(4) * p, p);
}

TEST(Matrix, vector_identity_multiplication) {
    RayTracer::Spatial::Vector v(1, 2, 3);
    EXPECT_EQ(RayTracer::Spatial::Matrix::get_identity(4) * v, v);
}

TEST(Matrix, tranpose) {
    RayTracer::Spatial::Matrix a({
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8},
    });
    EXPECT_EQ(a.transpose(), RayTracer::Spatial::Matrix({
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8},
    }));
}
