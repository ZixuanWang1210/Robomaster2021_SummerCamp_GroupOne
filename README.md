# Robomaster2021_SummerCamp_GropOne

## Task_One

终端运行指令
'''
		cd ~/catkin_ws
		catkin_make
		source devel/setup.bash
		roscore
		rosrun turtlesim turtlesim_node
		rosrun turtlesim_tf_follow turtle_tf_broadcaster __name:=turtle1_tf_broadcaster /turtle1
		rosrun turtlesim_tf_follow turtle_tf_broadcaster __name:=turtle2_tf_broadcaster /turtle2
		rosrun turtlesim_tf_follow turtle_tf_broadcaster __name:=turtle3_tf_broadcaster /turtle3
		rosrun turtlesim_tf_follow turtle_tf_listener
		rosrun turtlesim turtle_teleop_key
'''

部分重要代码
'''cpp
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
'''

运行效果
![](https://ftp.bmp.ovh/imgs/2021/07/94be9425507a9f91.jpg)

***
## Task_Two

终端运行指令
'''cpp
roslaunch remap_launch simple_plus.launch
'''
或
'''cpp
roscore
rosrun turtlesim turtlesim_node
rosservice call /spawn "x: 0.0 y: 0.0 theta: 0.0 name: 'turtle2'" 
roslaunch remap_launch simple.launch
'''

部分重要代码
'''HTML
<launch>
    <node pkg="turtlesim" type="turtle_teleop_key" name="turtle_teleop_key_as" output="screen">
        <remap from="/turtle1/cmd_vel" to="/turtle2/cmd_vel" /> 
    </node>
</launch>
'''
或
'''HTML
<node pkg="turtlesim" name="mimic" type="mimic">
<remap from="input" to="turtlesim1/turtle1"/>
<remap from="output" to="turtlesim2/turtle1"/>
</node>
'''

## Task_Three
终端运行指令
'''cpp
rosrun odom_publish odometry_publisher
rviz
'''
运行效果
![](https://ftp.bmp.ovh/imgs/2021/07/a8e2cd21452a63b0.jpg)
