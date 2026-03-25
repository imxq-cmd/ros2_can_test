#include "can_test_cpp/can_sender.hpp"

#include <chrono>
#include <memory>
#include <string>

using namespace drivers::socketcan;
using namespace std::chrono_literals;

namespace can_test_cpp
{

CanSender::CanSender(const std::string & name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(), "节点的名称为: %s.", name.c_str());

    // 创建发送器对象
    can_sender_ = std::make_shared<SocketCanSender>(
        "vcan0",             // CAN 接口
        false,              // 禁用快速模式
        CanId(
            0x123,          // 默认ID，如果要更改，可以在发送时覆盖
            0,              // 时间戳，0表示立即发送
            FrameType::DATA, // 数据帧
            StandardFrame_{}) // 标准格式
    );

    /* 创建定时器 (500毫秒一次) */
    timer_ = this->create_wall_timer(
        500ms, std::bind(&CanSender::TimerCallback, this));
}

void CanSender::TimerCallback()
{
    RCLCPP_INFO(this->get_logger(), "回调函数！");
    
    unsigned char messages[] = {0xCE, 0xBD, 0xEE, 0xFF}; // 发送的数据内容，在此更改需求
    
    try {
        can_sender_->send(
            messages,
            4,               // 发送的数据长度
            CanId(
                0x123,       // 发送ID，在此更改ID
                0,
                FrameType::DATA,
                StandardFrame_{}),
            100ms            // 超时时间
        );
    } catch (const std::exception & e) {
        RCLCPP_ERROR(this->get_logger(), "发送失败: %s", e.what());
    }
}

}  // namespace can_test_cpp

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<can_test_cpp::CanSender>("can_sender");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
