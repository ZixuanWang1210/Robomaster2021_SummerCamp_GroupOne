/***********************************************************************
Copyright 2020 GuYueHome (www.guyuehome.com).
***********************************************************************/

/**
 * 该例程监听tf数据，并计算、发布turtle2的速度指令
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv)
{
	// 初始化ROS节点
	ros::init(argc, argv, "my_tf_listener");

    // 创建节点句柄
	ros::NodeHandle node;

	// 请求产生turtle2 and 3
	ros::service::waitForService("/spawn");
	ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("/spawn");
	turtlesim::Spawn srv;
	add_turtle.call(srv);

	ros::service::waitForService("/spawn");
	ros::ServiceClient add_turtle1 = node.serviceClient<turtlesim::Spawn>("/spawn");
	turtlesim::Spawn srv1;
	add_turtle1.call(srv1);

	// 创建发布turtle2速度控制指令的发布者
	ros::Publisher turtle_vel2 = node.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);
	ros::Publisher turtle_vel3 = node.advertise<geometry_msgs::Twist>("/turtle3/cmd_vel", 10);

	// 创建tf的监听器
	tf::TransformListener listener1;
	tf::TransformListener listener2;
	ros::Rate rate(10.0);
	while (node.ok())
	{
		// 获取turtle1与turtle2坐标系之间的tf数据
		tf::StampedTransform transform2;
		tf::StampedTransform transform3;
		try
		{
			listener1.waitForTransform("/turtle2", "/turtle1", ros::Time(0), ros::Duration(3.0));
			listener2.waitForTransform("/turtle3", "/turtle1", ros::Time(0), ros::Duration(3.0));
			listener1.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform2);
			listener2.lookupTransform("/turtle3", "/turtle1", ros::Time(0), transform3);		
		}
		catch (tf::TransformException &ex) 
		{
			ROS_ERROR("%s",ex.what());
			ros::Duration(1.0).sleep();
			continue;
		}

		// 根据turtle1与turtle2坐标系之间的位置关系，发布turtle2的速度控制指令
		geometry_msgs::Twist vel_msg2;
		vel_msg2.angular.z = 4.0 * atan2(transform2.getOrigin().y(),
				                        transform2.getOrigin().x());
		vel_msg2.linear.x = 0.5 * sqrt(pow(transform2.getOrigin().x() + 10, 2) +
				                      pow(transform2.getOrigin().y() + 10, 2));
		turtle_vel2.publish(vel_msg2);

		geometry_msgs::Twist vel_msg3;
		vel_msg3.angular.z = 4.0 * atan2(transform3.getOrigin().y(),
				                        transform3.getOrigin().x());
		vel_msg3.linear.x = 0.5 * sqrt(pow(transform3.getOrigin().x() + 5, 2) +
				                      pow(transform3.getOrigin().y() + 5, 2));
		turtle_vel3.publish(vel_msg3);

		rate.sleep();
	}
	return 0;
};
