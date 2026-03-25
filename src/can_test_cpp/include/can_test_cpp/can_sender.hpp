#ifndef CAN_TEST_CPP__CAN_SENDER_HPP_
#define CAN_TEST_CPP__CAN_SENDER_HPP_

#include <memory>
#include <string>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "ros2_socketcan/socket_can_sender.hpp"
#include "ros2_socketcan/socket_can_receiver.hpp"
#include "can_msgs/msg/frame.hpp"

namespace can_test_cpp
{

class CanSender : public rclcpp::Node
{
public:
    explicit CanSender(const std::string & name);

private:
    void TimerCallback();

    std::shared_ptr<drivers::socketcan::SocketCanSender> can_sender_;
    rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace can_test_cpp

#endif  // CAN_TEST_CPP__CAN_SENDER_HPP_
