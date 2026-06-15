#include <uavcan_linux/uavcan_linux.hpp>

uavcan::ISystemClock& getSystemClock()
{
    static uavcan_linux::SystemClock clock;
    return clock;
}

uavcan::ICanDriver& getCanDriverCAN0()
{
    static uavcan_linux::SocketCanDriver driverCAN0(dynamic_cast<const uavcan_linux::SystemClock&>(getSystemClock()));
    //if (driverCAN0.getNumIfaces() == 0)     // Will be executed once
    //{
        if (driverCAN0.addIface("can0") < 0)
        {
            throw std::runtime_error("Failed to add iface");
        }
    //}
    return driverCAN0;
}

uavcan::ICanDriver& getCanDriverCAN1()
{
    static uavcan_linux::SocketCanDriver driverCAN1(dynamic_cast<const uavcan_linux::SystemClock&>(getSystemClock()));

    if (driverCAN1.addIface("can1") < 0)
    {
        throw std::runtime_error("Failed to add iface");
    }

    return driverCAN1;
}
