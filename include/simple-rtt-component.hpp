/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#ifndef SIMPLERTTCOMPONENT_HPP
#define SIMPLERTTCOMPONENT_HPP

// RTT header files. Might missing some or some be unused
#include <rtt/RTT.hpp>
// For datatypes:
#include <rst-rt/kinematics/JointAngles.hpp>

#include <string>

#define ROBOT_DOF_SIZE 7

class RttComponent: public RTT::TaskContext {
public:
    RttComponent(std::string const & name);

    // RTT::TaskContext methods that are needed for any standard component and
    // should be implemented by user
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

private:
    // To sample ports
    //OutputPorts publish data.
    RTT::OutputPort<rstrt::kinematics::JointAngles> JntPos_outPort;

    //InputPorts read data.
    RTT::InputPort<rstrt::kinematics::JointAngles> JntPos_InPort;

    //InputPorts flow:
    RTT::FlowStatus JntPos_InFlow;

    //Hold the read[from port] value
    rstrt::kinematics::JointAngles currJntPos;

    //Hold the write[to port] value
    rstrt::kinematics::JointAngles outJntPos;

};

#endif // SIMPLERTTCOMPONENT_HPP
