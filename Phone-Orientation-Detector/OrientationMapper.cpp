/**
 * @file OrientationMapper.cpp
 * @brief Implements the orientation label mapping helper class.
 * @author Fabio Bustamante Romillo
 * @date April 2026
 */

#include "OrientationMapper.h"

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

std::string OrientationMapper::getOrientationName(int label) const {
    auto it = labelToOrientation.find(label);
    if (it != labelToOrientation.end()) {
        return it->second;
    }
    return "Unknown orientation";
}

bool OrientationMapper::isValidLabel(int label) const {
    return label >= 1 && label <= 6;
}