#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rmcs_executor/component.hpp>

namespace rmcs_core::controller::task {

class Input
    : public rmcs_executor::Component
    , public rclcpp::Node {
public:
    Input()
        : Node(
              get_component_name(),
              rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true)){
        register_input("/task/sin_value", sin_value_);
        register_input("/task/cos_value", cos_value_);
        register_output("/task/sum_value", sum_value_);
    }
            
    void update() override {
        *sum_value_ = *sin_value_ + *cos_value_;

        RCLCPP_INFO(get_logger(), "sin value:%lf", *sin_value_);
        RCLCPP_INFO(get_logger(), "cos value:%lf", *cos_value_);
        RCLCPP_INFO(get_logger(), "sum value:%lf", *sum_value_);
    }

private:
    InputInterface<double> sin_value_;
    InputInterface<double> cos_value_;
    OutputInterface<double> sum_value_;
};
}

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(rmcs_core::controller::task::Input, rmcs_executor::Component)