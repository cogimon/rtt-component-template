/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#include "simple-rtt-component.hpp"
// needed for the macro at the end of this file:
#include <rtt/Component.hpp>

// This macro is needed for joint mappings
#define JOINT_NAMES_MAPPING_LOOKUP( it, memberDict, remoteDict, jointName ) {it = remoteDict.find(#jointName); if (it != remoteDict.end()) { memberDict.jointName = it->second; } it = remoteDict.end(); }


ExampleLeftArm::ExampleLeftArm(std::string const & name) : cogimon::RTTJointAwareTaskContext(name) {
    // constructor:
    joint_position_left_arm_command = rstrt::kinematics::JointAngles(COMAN_LEFT_ARM_DOF_SIZE);
    joint_position_left_arm_command.angles.setZero();

    joint_position_left_arm_output_port.setName("JointPositionOutputPort_left_arm");
    joint_position_left_arm_output_port.setDataSample(joint_position_left_arm_command);

    ports()->addPort(joint_position_left_arm_output_port).doc("Output port for sending right arm refrence joint values");

    magnitude = 1.0;
    addProperty("trajectory_magnitude", magnitude).doc("Magnitude of sinusoidal trajectory");
}

bool ExampleLeftArm::configureHook() {
    // intializations and object creations go here. Each component should run this before being able to run
    if (!joint_position_left_arm_output_port.connected())
        return false;
    else
        return true;
}

bool ExampleLeftArm::startHook() {
    // this method starts the component

    // e.g., setting home configuration:
    joint_position_left_arm_command.angles(comanLeftArm.LElbj) = 0.5;
    joint_position_left_arm_output_port.write(joint_position_left_arm_command);

    return true;
}

void ExampleLeftArm::updateHook() {
    // this is the actual body of a component. it is called on each cycle
    for(int i=0; i<COMAN_LEFT_ARM_DOF_SIZE; ++i)
        joint_position_left_arm_command.angles(i) = magnitude*sin(getSimulationTime());

    joint_position_left_arm_output_port.write(joint_position_left_arm_command);
}

void ExampleLeftArm::stopHook() {
    // stops the component (update hook wont be  called anymore)
}

void ExampleLeftArm::cleanupHook() {
    // cleaning the component data
}

void ExampleLeftArm::retrieveJointMappingsHook(const std::string &port_name, const std::map<std::string, int> &mapping) {
    if (port_name == "JointPositionOutputPort_left_arm") {
        std::map<std::string, int>::const_iterator it;
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LShSag);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LShLat);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LShYaw);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LElbj);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LForearmPlate);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LWrj1);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LWrj2);
    } else {
        // handle the exception
    }
    typedef std::map<std::string, int>::const_iterator iterator;
    for (iterator it=mapping.begin(); it!=mapping.end(); ++it )
        RTT::log(RTT::Info) << it->first<<"\t"<<it->second<<RTT::endlog();
}

double ExampleLeftArm::getSimulationTime() {
    return 1E-9 * RTT::os::TimeService::ticks2nsecs(RTT::os::TimeService::Instance()->getTicks());
}

void ExampleLeftArm::processJointMappingsHook(){

}

// This macro, as you can see, creates the component. Every component should have this!
ORO_CREATE_COMPONENT_LIBRARY()ORO_LIST_COMPONENT_TYPE(ExampleLeftArm)
