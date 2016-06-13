/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#ifndef SIMPLERTTCOMPONENT_HPP
#define SIMPLERTTCOMPONENT_HPP

// RTT header files. Might missing some or some be unused
#include <rtt/Port.hpp>
#include <string>
#include <rtt-core-extensions/rtt-jointaware-taskcontext.hpp>

// Joint value datatype:
#include <rst-rt/kinematics/JointAngles.hpp>
// Joint names for convenience
#include "JointNameMappingsComanArms.hpp"

#define COMAN_RIGHT_ARM_DOF_SIZE 7

class RttComponent: public cogimon::RTTJointAwareTaskContext {
public:
    RttComponent(std::string const & name);

    void retrieveJointMappingsHook(std::string const& port_name, std::map<std::string, int> const& mapping);
    void processJointMappingsHook();

    // RTT::TaskContext methods that are needed for any standard component and
    // should be implemented by user
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

private:
    JointNamesLeftArm  comanLeftArm;
    JointNamesRightArm comanRightArm;

    // Declare ports and their datatypes
    RTT::OutputPort<rstrt::kinematics::JointAngles> joint_position_right_arm_output_port;

    // Actuall joint command to be sent over port:
    rstrt::kinematics::JointAngles joint_position_right_arm_command;

    // helpers:
    double getSimulationTime();
    double magnitude;
};

#endif // SIMPLERTTCOMPONENT_HPP
