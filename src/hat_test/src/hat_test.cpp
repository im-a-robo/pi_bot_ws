#include <chrono>
#include <functional>
#include <memory>
#include <ratio>
#include <rclcpp/logging.hpp>
#include <rclcpp/utilities.hpp>
#include <string>
#include <thread>

#include "motor_driver/motor_hat.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class HatTestNode : public rclcpp::Node {
   public:
    HatTestNode() : Node("hat_test"), hat_(0x60, 1600) {
        timer_ = this->create_wall_timer(500ms, std::bind(&HatTestNode::timer_callback, this));
    }

   private:
    void timer_callback() {
        invert = motor_pwr % 101 == 0 ? invert *= -1 : invert;
        motor_pwr = ((motor_pwr + 1) % 101) * invert;
        RCLCPP_INFO(this->get_logger(), "Running hat test node, setting motor power to %d",
                    motor_pwr);

        auto motor1 = hat_.get_motor(1);
        auto motor2 = hat_.get_motor(2);
        auto motor3 = hat_.get_motor(3);
        auto motor4 = hat_.get_motor(4);
        motor1->set_power(motor_pwr);
        motor2->set_power(motor_pwr);
        motor3->set_power(motor_pwr);
        motor4->set_power(motor_pwr);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    int motor_pwr = 0;
    int invert = 1;
    MotorHat hat_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HatTestNode>());
    rclcpp::shutdown();
    return 0;
}
