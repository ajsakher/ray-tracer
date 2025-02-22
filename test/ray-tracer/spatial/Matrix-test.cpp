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

    RayTracer::Spatial::Matrix b({
        {0, 9, 3, 0, 6},
        {9, 8, 0, 8, 4},
        {1, 8, 5, 3, 8},
        {0, 0, 5, 8, 2},
    });
    EXPECT_EQ(b.transpose(), RayTracer::Spatial::Matrix({
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8},
        {6, 4, 8, 2}
    }));

    EXPECT_EQ(
        RayTracer::Spatial::Matrix::get_identity(4).transpose(),
        RayTracer::Spatial::Matrix::get_identity(4)
    );
}

TEST(Matrix, determinant) {
    RayTracer::Spatial::Matrix a({
        {1, 5},
        {-3, 2},
    });
    EXPECT_EQ(a.determinant(), 17);

    a = RayTracer::Spatial::Matrix({
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4},
    });
    EXPECT_EQ(a.determinant(), -196);

    a = RayTracer::Spatial::Matrix({
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    });
    EXPECT_EQ(a.determinant(), -4071);
}

TEST(Matrix, submatrix) {
    RayTracer::Spatial::Matrix a({
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3},
    });
    EXPECT_EQ(
        RayTracer::Spatial::get_submatrix(a, 0, 2),
        RayTracer::Spatial::Matrix({
            {-3, 2},
            {0, 6},
        })
    );

    a = RayTracer::Spatial::Matrix({
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1},
    });
    EXPECT_EQ(
        RayTracer::Spatial::get_submatrix(a, 2, 1),
        RayTracer::Spatial::Matrix({
            {-6, 1, 6},
            {-8, 8, 6},
            {-7, -1, 1}
        })
    );
}

TEST(Matrix, minor) {
    RayTracer::Spatial::Matrix a({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    });
    EXPECT_EQ(RayTracer::Spatial::minor(a, 1, 0), 25);
}

TEST(Matrix, cofactor) {
    RayTracer::Spatial::Matrix a({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    });
    EXPECT_EQ(RayTracer::Spatial::cofactor(a, 0, 0), -12);
    EXPECT_EQ(RayTracer::Spatial::cofactor(a, 1, 0), -25);
}

TEST(Matrix, invert) {
    RayTracer::Spatial::Matrix m({
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    });
    RayTracer::Spatial::Matrix expected_inverted_m({
        {0.21805, 0.45113, 0.24060, -0.04511 },
        { -0.80827, -1.45677, -0.44361, 0.52068 },
        { -0.07895, -0.22368, -0.05263, 0.19737 },
        { -0.52256, -0.81391, -0.30075, 0.30639 }
    });
    EXPECT_EQ(m.invert(), expected_inverted_m);

    m = RayTracer::Spatial::Matrix({
        { 8, -5, 9, 2, },
        { 7, 5, 6, 1, },
        { -6, 0, 9, 6 },
        { -3, 0, -9, -4 }
    });
    expected_inverted_m = RayTracer::Spatial::Matrix({
        { -0.15385, -0.15385, -0.28205, -0.53846 },
        { -0.07692, 0.12308, 0.02564, 0.03077, },
        { 0.35897, 0.35897, 0.43590, 0.92308, },
        { -0.69231, -0.69231, -0.76923, -1.92308 },
    });
    EXPECT_EQ(m.invert(), expected_inverted_m);

    m = RayTracer::Spatial::Matrix({
        { 9, 3, 0, 9,},
        { -5, -2, -6, -3,},
        { -4, 9, 6, 4,},
        { -7, 6, 6, 2,},
    });
    expected_inverted_m = RayTracer::Spatial::Matrix({
       { -0.04074, -0.07778, 0.14444, -0.22222 },
       { -0.07778, 0.03333, 0.36667, -0.33333 },
       { -0.02901, -0.14630, -0.10926, 0.12963 },
       { 0.17778, 0.06667, -0.26667, 0.33333 },
    });
    EXPECT_EQ(m.invert(), expected_inverted_m);
}

TEST(Matrix, product_invert) {
    RayTracer::Spatial::Matrix m({
        { 3, -9, 7, 3 },
        { 3, -8, 2, -9 },
        { -4, 4, 4, 1 },
        { -6, 5, -1, 1 },
    });
    RayTracer::Spatial::Matrix n({
       { 8, 2, 2, 2 },
       { 3, -1, 7, 0 },
       { 7, 0, 5, 4 },
       { 6, -2, 0, 5 },
    });

    EXPECT_EQ(m * n * n.invert(), m);
}
