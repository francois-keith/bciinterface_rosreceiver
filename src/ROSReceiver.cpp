#include "bci-interface/CommandReceiver/ROSReceiver.h"

#include "bciinterface_rosreceiver_msgs/BCICommand.h"

namespace bciinterface
{

struct ROSReceiverImpl
{
    ROSReceiverImpl(ros::NodeHandle & nh) : seq(0)
    {
        pub = nh.advertise<bciinterface_rosreceiver_msgs::BCICommand>("bci_command", 10);
    }

    ~ROSReceiverImpl()
    {
    }

    ros::Publisher pub;
    uint32_t seq;
};

ROSReceiver::ROSReceiver(ros::NodeHandle & nh, short port)
: UDPReceiver(port), impl(new ROSReceiverImpl(nh))
{
}

ROSReceiver::~ROSReceiver()
{
}

int ROSReceiver::GetCommand()
{
    int cmd = UDPReceiver::GetCommand();

    bciinterface_rosreceiver_msgs::BCICommandPtr msg(new bciinterface_rosreceiver_msgs::BCICommand);
    msg->header.seq = ++(impl->seq);
    msg->header.stamp = ros::Time::now();
    msg->cmd = cmd;
    impl->pub.publish(msg);

    return cmd;
}


} //namespace bciinterface

