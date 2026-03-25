#include "can_test_cpp/can_receiver.hpp"

#include <chrono>
#include <memory>
#include <string>
#include <vector>

using namespace drivers::socketcan;
using namespace std::chrono_literals;

namespace can_test_cpp
{

CanReceiver::CanReceiver(const std::string & name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(), "节点的名称为: %s.", name.c_str());
    
    // 初始化接收器
    can_receiver_ = std::make_shared<SocketCanReceiver>(
        "vcan0",     // 绑定的 CAN 接口
        false       // 是否使用高速 CAN (CAN-FD)
    );

    // 创建定时器 (500ms 检查一次接收)
    timer_ = this->create_wall_timer(
        500ms, std::bind(&CanReceiver::TimerCallback, this));
}

void CanReceiver::TimerCallback()
{
    try {
        unsigned char message[4] = {0}; // 接受的数据大小一定要与发送一致，否则接受节点会报错
        
        // 尝试接收数据，超时设置为 100微秒
        can_id_ = can_receiver_->receive(message, 100us);
        
        RCLCPP_INFO(
            this->get_logger(),
            "收到数据 - ID: 0x%X, 扩展帧: %s, 帧类型: %d, 数据长度: %u",
            can_id_.get(), 
            can_id_.is_extended() ? "是" : "否", 
            static_cast<int>(can_id_.frame_type()),
            can_id_.length()
        );

        for (uint32_t i = 0; i < can_id_.length(); ++i) {
            RCLCPP_INFO(this->get_logger(), "  数据[%d]: 0x%02X", i, message[i]);
        }
    }
    catch (const SocketCanTimeout & e) {
        // 超时是常态，不需要处理
    }
    catch (const std::exception & e) {
        RCLCPP_ERROR(this->get_logger(), "接收错误: %s", e.what());
    }
}

}  // namespace can_test_cpp

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<can_test_cpp::CanReceiver>("can_receiver");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
