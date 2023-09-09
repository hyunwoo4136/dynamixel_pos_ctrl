#include <ros/ros.h>
#include "std_msgs/Int16.h"
#include "dynamixel_workbench_msgs/DynamixelCommand.h"


///////////////////////////////////////////////////////////////////////////	var. declaration
bool send_flag=false;

int pos;


///////////////////////////////////////////////////////////////////////////	cmd call back func.
void cmd_callback(const std_msgs::Int16::ConstPtr& msg)
{
	send_flag=true;
	
	pos=msg->data;
}


///////////////////////////////////////////////////////////////////////////	main function
int main(int argc, char **argv)
{
	ros::init(argc, argv, "dynamixel_pos_ctrl");
	ros::NodeHandle nh;
	
	ros::Rate loop_rate(5);
	
	ros::Subscriber cmd_sub;							// subscriber declaration
	cmd_sub=nh.subscribe("cmd_pos", 10, cmd_callback);
	
	ros::ServiceClient client_cmd;						// service client declaration
	client_cmd=nh.serviceClient<dynamixel_workbench_msgs::DynamixelCommand>("/dynamixel_workbench/dynamixel_command");
	
	dynamixel_workbench_msgs::DynamixelCommand cmd;		// service request declaration
	
	cmd.request.command="";
	cmd.request.id=0;
	cmd.request.addr_name="Goal_Position";
	
	while(ros::ok())
	{
		ros::spinOnce();
		
		if(send_flag==true)
		{
			cmd.request.value=pos;
			client_cmd.call(cmd);
			
			send_flag=false;
		}
		
		loop_rate.sleep();
	}
	
	return 0;					
}
