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


RttComponent::RttComponent(std::string const & name) : cogimon::RTTJointAwareTaskContext(name) {
    // constructor:
    
}

bool RttComponent::configureHook() {
    // intializations and object creations go here. Each component should run this before being able to run
    return true;
}

bool RttComponent::startHook() {
    // this method starts the component
    return true;
}

void RttComponent::updateHook() {
    // this is the actual body of a component. it is called on each cycle
}

void RttComponent::stopHook() {
    // stops the component (update hook wont be  called anymore)
}

void RttComponent::cleanupHook() {
    // cleaning the component data
}

void RttComponent::retrieveJointMappingsHook(const std::string &port_name, const std::map<std::string, int> &mapping) {
    if (port_name == "cmdJntPos") {
        std::map<std::string, int>::const_iterator it;
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LShSag);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LShLat);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LShYaw);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LElbj);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LForearmPlate);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LWrj1);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanLeftArm, mapping, LWrj2);
    } else if (port_name == "cmdJntPosRIGHT") {
        std::map<std::string, int>::const_iterator it;
        JOINT_NAMES_MAPPING_LOOKUP(it, comanRightArm, mapping, RShSag);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanRightArm, mapping, RShLat);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanRightArm, mapping, RShYaw);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanRightArm, mapping, RElbj);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanRightArm, mapping, RForearmPlate);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanRightArm, mapping, RWrj1);
        JOINT_NAMES_MAPPING_LOOKUP(it, comanRightArm, mapping, RWrj2);
    } else {
        // handle the exception
    }
}

void RttComponent::processJointMappingsHook(){

}

// This macro, as you can see, creates the component. Every component should have this!
ORO_CREATE_COMPONENT_LIBRARY()ORO_LIST_COMPONENT_TYPE(RttComponent)
