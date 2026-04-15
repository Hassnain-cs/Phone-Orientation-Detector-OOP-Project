#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Helper function to convert label number to orientation name
// Used internally to set the orientationName field
static std::string getLabelName(int label) {
    if (label == 1) return "Face up";
    if (label == 2) return "Face down";
    if (label == 3) return "Portrait";
    if (label == 4) return "Portrait upside down";
    if (label == 5) return "Landscape left";
    if (label == 6) return "Landscape right";
    return "Unknown";
}

// Reads training data from file
// Each line format: x,y,z,label
// Returns number of samples read, or -1 if file not found
int FileHandler::loadTrainingData(const std::string& filename,
    std::vector<double>& outXValues,
    std::vector<double>& outYValues,
    std::vector<double>& outZValues,
    std::vector<int>& outLabels) {

    std::ifstream file(filename);

    // Check if file opened successfully
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file: " << filename << std::endl;
        return -1;
    }

    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        double x, y, z;
        int label;

        // Parse x
        std::getline(ss, token, ',');
        x = std::stod(token);

        // Parse y
        std::getline(ss, token, ',');
        y = std::stod(token);

        // Parse z
        std::getline(ss, token, ',');
        z = std::stod(token);

        // Parse label
        std::getline(ss, token, ',');
        label = std::stoi(token);

        // Store into output vectors
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
// Each line format: x,y,z
// Returns vector of DataPoint objects with label set to -1
std::vector<DataPoint> FileHandler::loadUnknownData(const std::string& filename) {

    std::vector<DataPoint> points;
    std::ifstream file(filename);

    // Check if file opened successfully
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open file: " << filename << std::endl;
        return points;
    }

    std::string line;

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        double x, y, z;

        // Parse x
        std::getline(ss, token, ',');
        x = std::stod(token);

        // Parse y
        std::getline(ss, token, ',');
        y = std::stod(token);

        // Parse z
        std::getline(ss, token, ',');
        z = std::stod(token);

        // Create DataPoint with label -1 (unknown)
        DataPoint dp(x, y, z, -1);
        points.push_back(dp);
    }

    file.close();
    return points;
}

// Writes classification results to output file
// Each line format: x,y,z,label,orientationName
// Returns true if successful, false otherwise
bool FileHandler::saveResults(const std::string& filename,
    const std::vector<DataPoint>& results) {

    std::ofstream file(filename);

    // Check if file opened successfully
    if (!file.is_open()) {
        std::cout << "ERROR: Could not create file: " << filename << std::endl;
        return false;
    }

    // Write each result as a line
    for (int i = 0; i < results.size(); i++) {
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

// Shows training data distribution after loading
// Extra credit: displays count and percentage per orientation
void FileHandler::showTrainingStatistics(const std::vector<int>& labels) {

    int total = labels.size();

    // Count how many samples per label
    int counts[7] = { 0 }; // index 1 to 6
    for (int i = 0; i < labels.size(); i++) {
        int label = labels[i];
        if (label >= 1 && label <= 6) {
            counts[label]++;
        }
    }

    std::cout << std::endl;
    std::cout << "Training Data Loaded Successfully!" << std::endl;
    std::cout << "-> Total samples: " << total << std::endl;
    std::cout << "-> Distribution:" << std::endl;

    // Print each orientation
    for (int label = 1; label <= 6; label++) {
        double percent = (counts[label] * 100.0) / total;
        std::cout << "   " << getLabelName(label)
            << ": " << counts[label]
            << " samples ("
            << (int)percent << "%)"
            << std::endl;
    }
    std::cout << std::endl;
}

// Checks all data points for values outside [-1, 1]
// Warns user and auto corrects them
// Extra credit: outlier detection
int FileHandler::validateAndFixData(std::vector<DataPoint>& points) {

    int fixedCount = 0;

    for (int i = 0; i < points.size(); i++) {

        // Check if this point has invalid values
        if (!points[i].areGravityValuesValid()) {

            // Warn the user about each bad value
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

            // Auto correct the values
            points[i].clampGravityValues();
            std::cout << "-> Auto-corrected to valid range" << std::endl;

            fixedCount++;
        }
    }

    return fixedCount;
}