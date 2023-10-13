#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

class DriveBot {
public:
    DriveBot() {
        _motor_command_publisher = _n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
        _server = _n.advertiseService("ball_chaser/command_robot", &DriveBot::handle_drive_request, this);
    }

    bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res) {
        ROS_INFO("Drive request received\nx:%.2f \nyaw:%.2f", req.linear_x, req.angular_z);
        geometry_msgs::Twist drive_comm;
        drive_comm.linear.x = req.linear_x;
        drive_comm.angular.z = req.angular_z;
        _motor_command_publisher.publish(drive_comm);
        res.msg_feedback = "Robot is moving with given request numbers";
         return true;
    }

private:
    ros::Publisher _motor_command_publisher;
    ros::NodeHandle _n;
    ros::ServiceServer _server;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "drive_bot_node");
    DriveBot drive_bot;
    ros::spin();
    return 0;
}
