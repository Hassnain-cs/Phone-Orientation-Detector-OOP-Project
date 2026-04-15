// OrientationMapper.cpp
// Implementation of orientation string mapping
// Maps numeric labels 1-6 to human readable orientation names

#include "OrientationMapper.h"

// Constructor - sets up the mappings
OrientationMapper::OrientationMapper() {
    initializeMap();
}

// Setup mappings based on the assignment table
// Label 1 = Face up, 2 = Face down, 3 = Portrait
// 4 = Portrait upside down, 5 = Landscape left, 6 = Landscape right
void OrientationMapper::initializeMap() {
    labelToOrientation[1] = "Face up";
    labelToOrientation[2] = "Face down";
    labelToOrientation[3] = "Portrait";
    labelToOrientation[4] = "Portrait upside down";
    labelToOrientation[5] = "Landscape left";
    labelToOrientation[6] = "Landscape right";
}

// Convert label number to readable orientation string
std::string OrientationMapper::getOrientationName(int label) const {
    auto it = labelToOrientation.find(label);
    if (it != labelToOrientation.end()) {
        return it->second;
    }
    return "Unknown orientation";
}

// Check if a label is within valid range of 1 to 6
bool OrientationMapper::isValidLabel(int label) const {
    return label >= 1 && label <= 6;
}