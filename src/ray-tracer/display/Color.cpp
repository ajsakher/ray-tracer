#include <ray-tracer/core/util.hpp>
#include <ray-tracer/display/Color.hpp>

namespace RayTracer {
namespace Display {

Color Color::operator+(const Color& c) const {
    return Color(
        this->red + c.red,
        this->green + c.green,
        this->blue + c.blue
    );
}

Color& Color::operator+=(const Color& c) {
    this->red += c.red;
    this->green += c.green;
    this->blue += c.blue;
    return *this;
}

Color Color::operator-(const Color& c) const {
    return Color(
        this->red - c.red,
        this->green - c.green,
        this->blue - c.blue
    );
}

Color& Color::operator-=(const Color& c) {
    this->red -= c.red;
    this->green -= c.green;
    this->blue -= c.blue;
    return *this;
}

Color Color::operator*(const double scalar) const {
    return Color(
        this->red * scalar,
        this->green * scalar,
        this->blue * scalar
    );
}

Color& Color::operator*=(const double scalar) {
    this->red *= scalar;
    this->green *= scalar;
    this->blue *= scalar;
    return *this;
}

Color Color::operator*(const Color& c) const {
    return Color(
        this->red * c.red,
        this->green * c.green,
        this->blue * c.blue
    );
}

Color& Color::operator*=(const Color& c) {
    this->red *= c.red;
    this->green *= c.green;
    this->blue *= c.blue;
    return *this;
}

bool Color::operator==(const Color& c) const {
    return Core::essentially_equal(this->red, c.red) &&
        Core::essentially_equal(this->green, c.green) &&
        Core::essentially_equal(this->blue, c.blue);
}

}
}
