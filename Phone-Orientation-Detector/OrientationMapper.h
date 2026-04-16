/**
 * @file OrientationMapper.h
 * @brief Declares a helper class for mapping numeric labels to orientation names.
 * @author Fabio Bustamante Romillo
 * @date April 2026
 */

#ifndef ORIENTATIONMAPPER_H
#define ORIENTATIONMAPPER_H

#include <string>
#include <map>

 /**
  * @class OrientationMapper
  * @brief Maps numeric orientation labels to human-readable names.
  *
  * This helper class stores a mapping between label values and readable
  * phone orientation descriptions such as Face up or Landscape left.
  */
class OrientationMapper {
private:
    /** @brief Internal map from numeric label to orientation name. */
    std::map<int, std::string> labelToOrientation;

    /**
     * @brief Initializes the label-to-orientation map.
     */
    void initializeMap();

public:
    /**
     * @brief Constructs an OrientationMapper object.
     */
    OrientationMapper();

    /**
     * @brief Returns the orientation name for a given label.
     * @param label Numeric orientation label.
     * @return Human-readable orientation string.
     */
    std::string getOrientationName(int label) const;

    /**
     * @brief Checks whether a label is within the valid range.
     * @param label Numeric orientation label.
     * @return True if the label is valid, otherwise false.
     */
    bool isValidLabel(int label) const;
};

#endif