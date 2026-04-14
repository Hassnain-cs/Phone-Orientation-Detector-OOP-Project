#include "OrientationMapper.h"

// Constructor
OrientationMapper::OrientationMapper() {
    initializeMap();
}

// Setup mappings based on assignment table
void OrientationMapper::initializeMap() {

    labelToOrientation[1] = "Face up";
    labelToOrientation[2] = "Face down";
    labelToOrientation[3] = "Portrait";
    labelToOrientation[4] = "Portrait upside down";
    labelToOrientation[5] = "Landscape left";
    labelToOrientation[6] = "Landscape right";
}

// Convert label ? readable orientation
std::string OrientationMapper::getOrientation(int label) const {
    auto it = labelToOrientation.find(label);

    if (it != labelToOrientation.end()) {
        return it->second;
    }

    return "Unknown orientation";
}

// Validate label range
bool OrientationMapper::isValidLabel(int label) const {
    return label >= 1 && label <= 6;
}
