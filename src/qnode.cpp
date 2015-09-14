/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/Bool.h>
#include <sstream>
#include "../include/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace leap_node {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode()
{
    if(ros::isStarted())
    {
      ros::shutdown();          // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init()
{
    ros::init( init_argc, init_argv, "Leap_node" );

    if ( ! ros::master::check() )
    {
		return false;
	}

	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;

	// Add your ros communications here.
    leap_publisher = n.advertise<std_msgs::Bool>("LeapState", 1000);

	start();

	return true;
}

void QNode::run()
{
    ros::Rate   loop_rate(1);
    int         count = 0;

    while ( ros::ok() )
    {
 //       std_msgs::Bool      msg;

//        leap_publisher.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();

		++count;
	}

	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;

    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::publishStateSlot(bool state)
{
    std_msgs::Bool      msg;
    msg.data = state;

    leap_publisher.publish(msg);
}

}  // namespace qt_test_pkg
