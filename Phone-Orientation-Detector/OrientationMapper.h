#ifndef ORIENTATIONMAPPER_H
#define ORIENTATIONMAPPER_H

#include <string>
#include <map>

class OrientationMapper {
private:
    std::map<int, std::string> labelToOrientation;

    void initializeMap();

public:
    OrientationMapper();

    std::string getOrientationName(int label) const;
    bool isValidLabel(int label) const;
};

#endif

