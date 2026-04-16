/**
 * @file DataPoint.h
 * @brief Defines the DataPoint structure used to store one gravity sample.
 * @author Raj Bahadur Bhat
 * @date April 2026
 */

#pragma once
#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>

 /**
  * @struct DataPoint
  * @brief Stores one 3D gravity sample and its orientation result.
  *
  * This structure is used for both input samples and classified output samples.
  * It stores the x, y, and z gravity values along with the numeric label and
  * readable orientation name.
  */
struct DataPoint {
    /** @brief Gravity value on the x-axis. */
    double xAxis;

    /** @brief Gravity value on the y-axis. */
    double yAxis;

    /** @brief Gravity value on the z-axis. */
    double zAxis;

    /** @brief Orientation label from 1 to 6, or -1 if unknown. */
    int orientationLabel;

    /** @brief Human-readable orientation name such as "Face up". */
    std::string orientationName;

    /**
     * @brief Default constructor.
     *
     * Initializes all gravity values to zero, the label to -1,
     * and the orientation name to an empty string.
     */
    DataPoint();

    /**
     * @brief Constructs a DataPoint with gravity values and an optional label.
     * @param xVal X-axis gravity value.
     * @param yVal Y-axis gravity value.
     * @param zVal Z-axis gravity value.
     * @param label Orientation label, default is -1 for unknown data.
     */
    DataPoint(double xVal, double yVal, double zVal, int label = -1);

    /**
     * @brief Checks whether the gravity values are within the valid range.
     * @return True if all x, y, and z values are between -1 and 1, otherwise false.
     */
    bool areGravityValuesValid() const;

    /**
     * @brief Clamps all gravity values into the valid range of -1 to 1.
     */
    void clampGravityValues();

    /**
     * @brief Converts the data point into a comma-separated string.
     * @return Formatted string containing x, y, z, label, and orientation name.
     */
    std::string convertToString() const;
};

#endif