/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#include "simple-rtt-component.hpp"
// needed for the macro at the end of this file:
#include <rtt/Component.hpp>

RttComponent::RttComponent(std::string const & name) :
    RTT::TaskContext(name),
    JntPos_outPort("JntPos_out", 0.0),
    JntPos_InPort("JntPos_in"),
    JntPos_InFlow(RTT::NoData) {

    // adding ports and some documentation which will be visible in e.g, deployer
    this->ports()->addPort(JntPos_outPort).doc("Sending joint position commands.");
    this->ports()->addPort(JntPos_InPort).doc("Receiving current joint position.");

    // initialize the actual value on the input and output ports and set it to zero.
    this->currJntPos = rstrt::kinematics::JointAngles(ROBOT_DOF_SIZE);
    this->currJntPos.angles.setZero();

    this->outJntPos = rstrt::kinematics::JointAngles(ROBOT_DOF_SIZE);
    this->outJntPos.angles.setZero();
}

bool RttComponent::configureHook() {
    // intializations and object creations go here. Each component should run this before being able to run

    // you can check if ports are connected and if so, return true:
    if (!(JntPos_outPort.connected() && JntPos_InPort.connected())){
        return false;
    } else {
        return true;
    }
}

bool RttComponent::startHook() {
    // this method starts the component
    return true;
}

void RttComponent::updateHook() {
    // this is the actual body of a component. it is called on each cycle
    // at first, it is a good idea to check if new data is available at port:
    if (JntPos_InPort.connected()) {
        // read into "currJntPos" and save state of data into "currJntPos_Flow", which can be "NewData", "OldData" or "NoData".
        JntPos_InFlow = JntPos_InPort.read(currJntPos);
    } else {
        // handle the situation
    }

    if (JntPos_InFlow == RTT::NewData) {

    } else if (JntPos_InFlow == RTT::OldData) {

    } else if (JntPos_InFlow == RTT::NoData) {

    } else {
        // handle the error!
    }
}

void RttComponent::stopHook() {
    // stops the component (update hook wont be  called anymore)
}

void RttComponent::cleanupHook() {
    // cleaning the component data
}

// This macro, as you can see, creates the component. Every component should have this!
ORO_CREATE_COMPONENT_LIBRARY()ORO_LIST_COMPONENT_TYPE(RttComponent)
