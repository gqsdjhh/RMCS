#include <rclcpp/node.hpp>
#include <rmcs_executor/component.hpp>

namespace rmcs_core::controller::task {

class Output
    : public rmcs_executor::Component
    , public rclcpp::Node {
public:
    Output()
        : Node(
              get_component_name(),
              rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true)){
        register_output("/task/sin_value", sin_value_);
        register_output("/task/cos_value", cos_value_);

        input_ = get_parameter("omega").as_double();

        _start_time = this->now();
    }
            
    void update() override {
        *omega_ = input_;

        auto current_time = this->now() - _start_time;
        double t = current_time.seconds();
        
        *sin_value_ = std::sin((*omega_) * t);
        *cos_value_ = std::cos((*omega_) * t);
    }

private:
    OutputInterface<double> omega_;
    OutputInterface<double> sin_value_;
    OutputInterface<double> cos_value_;

    double input_;

    rclcpp::Time _start_time;
};
}

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(rmcs_core::controller::task::Output, rmcs_executor::Component)