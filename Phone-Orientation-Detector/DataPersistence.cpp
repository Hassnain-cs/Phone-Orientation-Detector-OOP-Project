// DataPersistence.cpp
// Implementation of data persistence operations

#include "DataPersistence.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Helper function to convert label number to orientation name
static std::string getLabelName(int label) {
    if (label == 1) return "Face up";
    if (label == 2) return "Face down";
    if (label == 3) return "Portrait";
    if (label == 4) return "Portrait upside down";
    if (label == 5) return "Landscape left";
    if (label == 6) return "Landscape right";
    return "Unknown";
}

// Reads training data from file (with labels)
int DataPersistence::read(const std::string& filename,
    std::vector<double>& outXValues,
    std::vector<double>& outYValues,
    std::vector<double>& outZValues,
    std::vector<int>& outLabels) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file: " << filename << std::endl;
        return -1;
    }

    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        double x, y, z;
        int label;

        std::getline(ss, token, ',');
        x = std::stod(token);

        std::getline(ss, token, ',');
        y = std::stod(token);

        std::getline(ss, token, ',');
        z = std::stod(token);

        std::getline(ss, token, ',');
        label = std::stoi(token);

        // Clamp to valid range
        if (x < -1.0) x = -1.0; if (x > 1.0) x = 1.0;
        if (y < -1.0) y = -1.0; if (y > 1.0) y = 1.0;
        if (z < -1.0) z = -1.0; if (z > 1.0) z = 1.0;

        outXValues.push_back(x);
        outYValues.push_back(y);
        outZValues.push_back(z);
        outLabels.push_back(label);

        count++;
    }

    file.close();
    return count;
}

// Reads unknown data file (no labels)
std::vector<DataPoint> DataPersistence::read(const std::string& filename) {

    std::vector<DataPoint> points;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file: " << filename << std::endl;
        return points;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        double x, y, z;

        std::getline(ss, token, ',');
        x = std::stod(token);

        std::getline(ss, token, ',');
        y = std::stod(token);

        std::getline(ss, token, ',');
        z = std::stod(token);

        DataPoint dp(x, y, z, -1);
        points.push_back(dp);
    }

    file.close();
    return points;
}

// Writes results to file
bool DataPersistence::write(const std::string& filename,
    const std::vector<DataPoint>& results) {

    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERROR: Could not create file: " << filename << std::endl;
        return false;
    }

    for (size_t i = 0; i < results.size(); i++) {
        file << results[i].xAxis << ","
            << results[i].yAxis << ","
            << results[i].zAxis << ","
            << results[i].orientationLabel << ","
            << results[i].orientationName << std::endl;
    }

    file.close();
    std::cout << "Results saved to: " << filename << std::endl;
    return true;
}

// Shows training data distribution
void DataPersistence::showTrainingStatistics(const std::vector<int>& labels) {

    int total = static_cast<int>(labels.size());
    int counts[7] = { 0 };

    for (size_t i = 0; i < labels.size(); i++) {
        int label = labels[i];
        if (label >= 1 && label <= 6) {
            counts[label]++;
        }
    }

    std::cout << std::endl;
    std::cout << "Training Data Loaded Successfully!" << std::endl;
    std::cout << "-> Total samples: " << total << std::endl;
    std::cout << "-> Distribution:" << std::endl;

    for (int label = 1; label <= 6; label++) {
        double percent = (counts[label] * 100.0) / total;
        std::cout << "   " << getLabelName(label)
            << ": " << counts[label]
            << " samples ("
            << static_cast<int>(percent) << "%)"
            << std::endl;
    }
    std::cout << std::endl;
}

// Validates and fixes out of range values
int DataPersistence::validateAndFixData(std::vector<DataPoint>& points) {

    int fixedCount = 0;

    for (size_t i = 0; i < points.size(); i++) {

        if (!points[i].areGravityValuesValid()) {

            if (points[i].xAxis < -1.0 || points[i].xAxis > 1.0) {
                std::cout << "WARNING: Data point #" << (i + 1)
                    << " has x = " << points[i].xAxis
                    << " (outside valid range [-1,1])" << std::endl;
            }
            if (points[i].yAxis < -1.0 || points[i].yAxis > 1.0) {
                std::cout << "WARNING: Data point #" << (i + 1)
                    << " has y = " << points[i].yAxis
                    << " (outside valid range [-1,1])" << std::endl;
            }
            if (points[i].zAxis < -1.0 || points[i].zAxis > 1.0) {
                std::cout << "WARNING: Data point #" << (i + 1)
                    << " has z = " << points[i].zAxis
                    << " (outside valid range [-1,1])" << std::endl;
            }

            points[i].clampGravityValues();
            std::cout << "-> Auto-corrected to valid range" << std::endl;

            fixedCount++;
        }
    }

    return fixedCount;
}