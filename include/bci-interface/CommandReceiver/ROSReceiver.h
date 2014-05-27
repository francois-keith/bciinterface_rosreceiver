#include <bci-interface/CommandReceiver/UDPReceiver.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <ros/ros.h>

#ifndef _H_ROSRECEIVER_H_
#define _H_ROSRECEIVER_H_

namespace sf
{
    class RenderWindow;
}

namespace bciinterface
{

struct ROSReceiverImpl;

class ROSReceiver : public UDPReceiver
{
public:
    ROSReceiver(ros::NodeHandle & nh, short port);

    virtual ~ROSReceiver();

    virtual int GetCommand();
private:
    boost::shared_ptr<ROSReceiverImpl> impl;
};

} // namespace bciinterface

#endif

