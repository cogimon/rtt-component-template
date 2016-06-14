/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#include "simple-rtt-component.hpp"
// needed for the macro at the end of this file:
#include <rtt/Component.hpp>


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
    std::cout<<"comanLeftArm.LElbj index is "<<comanLeftArm.LElbj<<std::endl;
    joint_position_left_arm_command.angles(comanLeftArm.LElbj) = -0.5;
    joint_position_left_arm_output_port.write(joint_position_left_arm_command);

    return true;
}

void ExampleLeftArm::updateHook() {
    // this is the actual body of a component. it is called on each cycle
    for(int i=0; i<COMAN_LEFT_ARM_DOF_SIZE; ++i)
        joint_position_left_arm_command.angles(i) = magnitude*sin(getSimulationTime());

    //joint_position_left_arm_output_port.write(joint_position_left_arm_command);
}

void ExampleLeftArm::stopHook() {
    // stops the component (update hook wont be  called anymore)
}

void ExampleLeftArm::cleanupHook() {
    // cleaning the component data
}

void ExampleLeftArm::retrieveJointMappingsHook(const std::string &port_name, const std::vector<std::pair<std::string, int>> &mapping) {
    if (port_name == "JointPositionOutputPort_left_arm") {
        for(unsigned int i = 0; i < mapping.size(); ++i)
        {
            if(mapping[i].first == "LShSag")
                comanLeftArm.LShSag = mapping[i].second;
            if(mapping[i].first == "LShLat")
                comanLeftArm.LShLat = mapping[i].second;
            if(mapping[i].first == "LShYaw")
                comanLeftArm.LShYaw = mapping[i].second;
            if(mapping[i].first == "LElbj")
                comanLeftArm.LElbj = mapping[i].second;
            if(mapping[i].first == "LForearmPlate")
                comanLeftArm.LForearmPlate = mapping[i].second;
            if(mapping[i].first == "LWrj1")
                comanLeftArm.LWrj1 = mapping[i].second;
            if(mapping[i].first == "LWrj2")
                comanLeftArm.LWrj2 = mapping[i].second;
        }

        std::cout<<"LShSag is "<<comanLeftArm.LShSag<<std::endl;
        std::cout<<"LShLat is "<<comanLeftArm.LShLat<<std::endl;
        std::cout<<"LShYaw is "<<comanLeftArm.LShYaw<<std::endl;
        std::cout<<"LElbj is "<<comanLeftArm.LElbj<<std::endl;
        std::cout<<"LForearmPlate is "<<comanLeftArm.LForearmPlate<<std::endl;
        std::cout<<"LLWrj1 is "<<comanLeftArm.LWrj1<<std::endl;
        std::cout<<"LLWrj2 is "<<comanLeftArm.LWrj2<<std::endl;

    } else {
        // handle the exception
    }

}

double ExampleLeftArm::getSimulationTime() {
    return 1E-9 * RTT::os::TimeService::ticks2nsecs(RTT::os::TimeService::Instance()->getTicks());
}

void ExampleLeftArm::processJointMappingsHook(){

}

// This macro, as you can see, creates the component. Every component should have this!
ORO_CREATE_COMPONENT_LIBRARY()ORO_LIST_COMPONENT_TYPE(ExampleLeftArm)
