// NNClassifier.cpp
// Implementation of the Nearest Neighbor classifier

#include "NNClassifier.h"
#include <cmath>
#include <limits>
#include <algorithm>

// Constructor, nothing special needed here
NNClassifier::NNClassifier() {
}

// Destructor
NNClassifier::~NNClassifier() {
}

// Calculates the straight line distance between two points in 3D space
// Using the standard Euclidean distance formula
double NNClassifier::calculateEuclideanDistance(double x1, double y1, double z1,
    double x2, double y2, double z2) const {
    double diffX = x1 - x2;
    double diffY = y1 - y2;
    double diffZ = z1 - z2;

    return std::sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
}

// Store the training data in our protected member variables
// This data will be used later when classifying new samples
void NNClassifier::train(const std::vector<double>& xValues,
    const std::vector<double>& yValues,
    const std::vector<double>& zValues,
    const std::vector<int>& labels) {
    trainingDataX = xValues;
    trainingDataY = yValues;
    trainingDataZ = zValues;
    trainingLabels = labels;
}

// Find the closest training sample to the given point
// Return the label of that closest sample
int NNClassifier::classify(double x, double y, double z) {
    // Check if we have any training data
    if (trainingDataX.empty()) {
        return -1;
    }

    double smallestDistance = std::numeric_limits<double>::max();
    int bestLabel = -1;

    // Loop through all training samples to find the nearest one
    for (size_t i = 0; i < trainingDataX.size(); i++) {
        double distance = calculateEuclideanDistance(x, y, z,
            trainingDataX[i],
            trainingDataY[i],
            trainingDataZ[i]);

        // If this sample is closer than our current best, update it
        if (distance < smallestDistance) {
            smallestDistance = distance;
            bestLabel = trainingLabels[i];
        }
    }

    return bestLabel;
}

// Creative addition - provides confidence percentage with the prediction
// Confidence is based on how much closer the nearest neighbor is compared to others
std::pair<int, double> NNClassifier::classifyWithConfidence(double x, double y, double z) {
    if (trainingDataX.empty()) {
        return std::make_pair(-1, 0.0);
    }

    // Collect all distances with their labels
    std::vector<std::pair<double, int>> allDistances;

    for (size_t i = 0; i < trainingDataX.size(); i++) {
        double dist = calculateEuclideanDistance(x, y, z,
            trainingDataX[i],
            trainingDataY[i],
            trainingDataZ[i]);
        allDistances.push_back(std::make_pair(dist, trainingLabels[i]));
    }

    // Sort by distance to find nearest neighbors
    std::sort(allDistances.begin(), allDistances.end());

    int predictedLabel = allDistances[0].second;
    double nearestDistance = allDistances[0].first;

    // Find the second nearest sample that has a different label
    double secondNearestDistance = nearestDistance;
    for (size_t i = 1; i < allDistances.size(); i++) {
        if (allDistances[i].second != predictedLabel) {
            secondNearestDistance = allDistances[i].first;
            break;
        }
    }

    // Calculate confidence as a percentage
    double confidencePercent;
    if (secondNearestDistance == 0.0) {
        confidencePercent = 100.0;
    }
    else {
        confidencePercent = (secondNearestDistance / (nearestDistance + secondNearestDistance)) * 100.0;
    }

    // Keep confidence within bounds
    if (confidencePercent < 0.0) confidencePercent = 0.0;
    if (confidencePercent > 100.0) confidencePercent = 100.0;

    return std::make_pair(predictedLabel, confidencePercent);
}

// Return the name of this classifier
std::string NNClassifier::getClassifierName() const {
    return "Nearest Neighbor Classifier";
}