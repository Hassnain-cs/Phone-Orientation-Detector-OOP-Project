#pragma once
// DataPoint.h
// Simple structure to hold a single gravity vector measurement
// This demonstrates encapsulation of related data

#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>

struct DataPoint {
    // Gravity values for the three axes
    double xAxis;
    double yAxis;
    double zAxis;

    // Orientation label (1 to 6, or -1 if unknown)
    int orientationLabel;

    // Human readable orientation string like "Face up"
    std::string orientationName;

    // Default constructor
    DataPoint();

    // Constructor with values
    DataPoint(double xVal, double yVal, double zVal, int label = -1);

    // Checks if gravity values are within valid range of -1 to 1
    bool areGravityValuesValid() const;

    // Forces values to be within the -1 to 1 range
    void clampGravityValues();

    // Converts the data point to a comma separated string
    std::string convertToString() const;
};

#endif