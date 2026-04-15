#include "DataPoint.h"
#include <sstream>
#include <iomanip>

// Default constructor
// Sets everything to zero and label to -1 (unknown)
DataPoint::DataPoint() {
    xAxis = 0.0;
    yAxis = 0.0;
    zAxis = 0.0;
    orientationLabel = -1;
    orientationName = "Unknown";
}

// Constructor with values
// Label defaults to -1 if not provided (for unknown data)
DataPoint::DataPoint(double xVal, double yVal, double zVal, int label) {
    xAxis = xVal;
    yAxis = yVal;
    zAxis = zVal;
    orientationLabel = label;
    orientationName = "Unknown";
}

// Checks if all gravity values are within the valid range of -1 to 1
bool DataPoint::areGravityValuesValid() const {
    if (xAxis < -1.0 || xAxis > 1.0) return false;
    if (yAxis < -1.0 || yAxis > 1.0) return false;
    if (zAxis < -1.0 || zAxis > 1.0) return false;
    return true;
}

// Forces values to stay within -1 to 1
// If the value goes beyond the allowed limit,
// it’s automatically limited to the maximum/minimum boundary
void DataPoint::clampGravityValues() {
    if (xAxis < -1.0) xAxis = -1.0;
    if (xAxis > 1.0) xAxis = 1.0;

    if (yAxis < -1.0) yAxis = -1.0;
    if (yAxis > 1.0) yAxis = 1.0;
    if (zAxis < -1.0) zAxis = -1.0;
    if (zAxis > 1.0) zAxis = 1.0;
}

// Converts data point to a comma separated string
// Example output: "-0.177, -0.045, -0.983, 1 (Face up)"
std::string DataPoint::convertToString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << xAxis << ", " << yAxis << ", " << zAxis;
    oss << ", " << orientationLabel;
    oss << " (" << orientationName << ")";
    return oss.str();
}