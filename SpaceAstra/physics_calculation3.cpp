#include <cmath>
#include <string>

namespace Physics {
    class Vector {
    private:
        double _x;
        double _y;

    public:
        double X() const {
            return _x;
        }

        void SetX(double value) {
            _x = value;
        }

        double Y() const {
            return _y;
        }

        void SetY(double value) {
            _y = value;
        }

        double Magnitude() const {
            return std::sqrt(_x * _x + _y * _y);
        }

        Vector UnitVector() const {
            double mag = Magnitude();
            return Vector(_x / mag, _y / mag);
        }

        Vector(double x, double y) : _x(x), _y(y) {}

        Vector() : Vector(0.0, 0.0) {}

        void UpdateByAddWith(const Vector& other) {
            _x += other.X();
            _y += other.Y();
        }

        void UpdateBySubWith(const Vector& other) {
            _x -= other.X();
            _y -= other.Y();
        }

        double Dot(const Vector& other) const {
            return _x * other.X() + _y * other.Y();
        }

        Vector operator+(const Vector& other) const {
            return Vector(_x + other.X(), _y + other.Y());
        }

        Vector operator-(const Vector& other) const {
            return Vector(_x - other.X(), _y - other.Y());
        }

        Vector operator*(double scalar) const {
            return Vector(_x * scalar, _y * scalar);
        }

        friend Vector operator*(double scalar, const Vector& vector) {
            return vector * scalar;
        }

        std::string ToString() const {
            return std::to_string(_x) + " " + std::to_string(_y);
        }
    };
}