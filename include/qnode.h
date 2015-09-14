/**
 * @file /include/qt_test_pkg/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_test_pkg_QNODE_HPP_
#define qt_test_pkg_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace leap_node {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread
{
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();

	bool init();
	void run();

public Q_SLOTS:
    void publishStateSlot( bool state );

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

private:
    int             init_argc;
    char**          init_argv;

    ros::Publisher  leap_publisher;
};

}  // namespace leap_node

#endif /* qt_test_pkg_QNODE_HPP_ */
