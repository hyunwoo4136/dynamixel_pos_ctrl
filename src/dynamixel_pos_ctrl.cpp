#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include "dynamixel_workbench_msgs/DynamixelCommand.h"


///////////////////////////////////////////////////////////////////////////	var. declaration


///////////////////////////////////////////////////////////////////////////	main function
int main(int argc, char **argv)
{
	ros::init(argc, argv, "dynamixel_pos_ctrl");
	ros::NodeHandle nh;
	
	ros::Rate loop_rate(5);
	
	ros::ServiceClient client_cmd;
	client_cmd=nh.serviceClient<dynamixel_workbench_msgs::DynamixelCommand>("/dynamixel_workbench/dynamixel_command");
	
	dynamixel_workbench_msgs::DynamixelCommand cmd;
	
	cmd.request.command="";
	cmd.request.id=0;
	cmd.request.addr_name="Goal_Position";
	cmd.request.value=3072;
	
	client_cmd.call(cmd);
	
	while(ros::ok())
	{
		ros::spinOnce();
		
		client_cmd.call(cmd);
		
		loop_rate.sleep();
	}
	
	return 0;					
}
