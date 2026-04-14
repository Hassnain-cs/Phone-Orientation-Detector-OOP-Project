#pragma once
// NNClassifier.h
// Nearest Neighbor classifier implementation
// Inherits from the abstract Classifier base class

#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include "Classifier.h"
#include <string>

class NNClassifier : public Classifier {
private:
    // Helper function to calculate Euclidean distance between two 3D points
    // Made private because it's only used internally by this class
    double calculateEuclideanDistance(double x1, double y1, double z1,
        double x2, double y2, double z2) const;

public:
    // Constructor
    NNClassifier();

    // Destructor
    ~NNClassifier();

    // Implementation of the pure virtual train function
    // Stores the training data in the protected member variables
    void train(const std::vector<double>& xValues,
        const std::vector<double>& yValues,
        const std::vector<double>& zValues,
        const std::vector<int>& labels) override;

    // Implementation of the pure virtual classify function
    // Finds the nearest neighbor and returns its label
    int classify(double x, double y, double z) override;

    // Returns the name of this classifier
    std::string getClassifierName() const override;

    // Additional creative feature, classifies with confidence percentage
    // Returns a pair containing the predicted label and confidence value
    std::pair<int, double> classifyWithConfidence(double x, double y, double z);
};

#endif