#include <vector>
#include "src/physics_calculation.cpp"

namespace Physics {
    class InertialFrameReference {
    private:
        static constexpr double GravityConst = 2.9;
        std::vector<BallMass> _ballMasses;

    public:
        const std::vector<BallMass>& BallMasses() const {
            return _ballMasses;
        }

        InertialFrameReference() {
            _ballMasses = std::vector<BallMass>();
        }

        void AddBallMass(const BallMass& ball) {
            _ballMasses.push_back(ball);
        }

        void RemoveBallMass(const BallMass& ball) {
            auto it = std::find(_ballMasses.begin(), _ballMasses.end(), ball);
            if (it != _ballMasses.end()) {
                _ballMasses.erase(it);
            }
        }

        void DoPhysics() {
            for (auto& mass : _ballMasses) {
                UpdateAcceleration(mass);
            }
            for (auto& mass : _ballMasses) {
                UpdatePosition(mass);
            }
        }

    private:
        void UpdateAcceleration(BallMass& ball) {
            Vector resultant;
            for (const auto& b : _ballMasses) {
                if (&b == &ball)
                    continue;
                Vector distance = b.Position - ball.Position;
                double distanceValue = distance.Magnitude();
                double accel = GravityConst * b.Mass / (distanceValue * distanceValue);
                resultant.UpdateByAddWith(accel * distance.UnitVector());
            }
            ball.Acceleration = resultant;
        }

        void UpdatePosition(BallMass& ball) {
            ball.Velocity.UpdateByAddWith(ball.Acceleration);
            ball.Position.UpdateByAddWith(ball.Velocity);
        }
    };
}