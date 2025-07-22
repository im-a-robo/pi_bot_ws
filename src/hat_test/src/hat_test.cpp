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
        int motor_pwr = 5;
        RCLCPP_INFO(this->get_logger(), "Running hat test node, setting motor power to %d",
                    motor_pwr);

        auto motor1 = hat_.get_motor(1);
        motor1->set_power(motor_pwr);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    MotorHat hat_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HatTestNode>());
    rclcpp::shutdown();
    return 0;
}
