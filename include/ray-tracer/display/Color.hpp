#ifndef RAYTRACER_DISPLAY_COLOR_HPP
#define RAYTRACER_DISPLAY_COLOR_HPP

namespace RayTracer {
namespace Display {

class Color {
private:
    double red;
    double green;
    double blue;
public:
    Color() : red(0), green(0), blue(0) {}
    Color(double r, double g, double b) : red(r), green(g), blue(b) {}

    double get_red() const { return this->red; }
    double get_green() const { return this->green; }
    double get_blue() const { return this->blue; }

    Color operator+(const Color&) const;
    Color& operator+=(const Color&);
    Color operator-(const Color&) const;
    Color& operator-=(const Color&);

    Color operator*(const double) const;
    Color& operator*=(const double);
    Color operator*(const Color&) const;
    Color& operator*=(const Color&);

    bool operator==(const Color&) const;
};

}
}

#endif // RAYTRACER_DISPLAY_COLOR_HPP
