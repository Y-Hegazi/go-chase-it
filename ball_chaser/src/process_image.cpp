#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "ball_chaser/DriveToTarget.h"

class ProcessImage {
public:
    ProcessImage() {
        _client = _n.serviceClient<ball_chaser::DriveToTarget>("ball_chaser/command_robot");
        _sub = _n.subscribe("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);
    }

    void process_image_callback(const sensor_msgs::Image& img) {
    	bool ball_flag = false;
    	int column = 0;
      	ball_chaser::DriveToTarget drive_comm;
      for (int i=0; i < img.height * img.step; i += 3)
    {
        if ((img.data[i] == 255) && (img.data[i+1] == 255) && (img.data[i+2] == 255)) // for RGB image
        {
            column = i % img.step;
 
            if (column < img.step/3){
                drive_comm.request.linear_x = 0.5;
                drive_comm.request.angular_z = 0.5;}
          
            else if (column < (img.step/3 * 2)){
                drive_comm.request.linear_x = 0.5;
                drive_comm.request.angular_z = 0.0; }
          
            else{
                drive_comm.request.linear_x = 0.5;
                drive_comm.request.angular_z = -0.5;}
            ball_flag = true;
            break;
         }
     }

     if (!ball_flag){
       drive_comm.request.linear_x = 0.0;
       drive_comm.request.angular_z = 0.0;}
      if (!_client.call(drive_comm))
                ROS_ERROR("Failed to call service command_robot");

    } 

private:
    ros::Subscriber _sub;
    ros::NodeHandle _n;
    ros::ServiceClient _client;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "process_image");
    ProcessImage process_image;
    ros::spin();
    return 0;
}
