#ifndef CAN_TEST_CPP__CAN_RECEIVER_HPP_
#define CAN_TEST_CPP__CAN_RECEIVER_HPP_

#include <memory>
#include <string>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "ros2_socketcan/socket_can_receiver.hpp"
#include "can_msgs/msg/frame.hpp"

namespace can_test_cpp
{

class CanReceiver : public rclcpp::Node
{
public:
    explicit CanReceiver(const std::string & name);

private:
    void TimerCallback();

    std::shared_ptr<drivers::socketcan::SocketCanReceiver> can_receiver_;
    rclcpp::TimerBase::SharedPtr timer_;
    drivers::socketcan::CanId can_id_;
};

}  // namespace can_test_cpp

#endif  // CAN_TEST_CPP__CAN_RECEIVER_HPP_
