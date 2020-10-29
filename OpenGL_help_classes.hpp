#pragma once

class Point {
public:

    double x;
    double y;

    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    void set() const {
        glVertex2d(x, y);
    }

    Point& operator+=(const Point &p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator-=(const Point &p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point operator+(const Point &p) const {
        Point n_p = *this;
        return n_p += p;
    }

    Point operator-(const Point &p) const {
        Point n_p = *this;
        return n_p -= p;
    }

    Point operator*(double k) const {
        return Point(k * x, k * y);
    }

    Point orthogonal() const {
        return Point(-y, x);
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    void set_normal() {
        double len = length();
        x /= len;
        y /= len;
    }

};

class Color {
public:
    
    double r;
    double g;
    double b;
    double a;

    explicit Color(double r, double g, double b, double a = 1.0) : r(r),    g(g),    b(b),    a(a)    {}
    explicit Color(int    r, int    g, int    b, int    a = 255) : r(H(r)), g(H(g)), b(H(b)), a(H(a)) {} 

    void set() const {
        glColor3d(r, g, b);
    }

};