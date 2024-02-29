#include <Vector>
#include "../physics_calculation3.cpp"

namespace Physics {
    class BallMass {
    public:
        double Radius;
        double Mass;

        Vector Position;
        Vector Velocity;
        Vector Acceleration;

        BallMass() : Radius(0), Mass(0), Position(Vector()), Velocity(Vector()), Acceleration(Vector()) {}

        void AddToVelocity(Vector vector) {
            Velocity.UpdateByAddWith(vector);
        }

        void AddToAcceleration(Vector vector) {
            Acceleration.UpdateByAddWith(vector);
        }
    };
}