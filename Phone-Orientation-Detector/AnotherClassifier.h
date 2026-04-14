#pragma once
// AnotherClassifier.h
// Stub classifier that is not fully implemented yet
// This demonstrates how new classifiers can be added to the system

#ifndef ANOTHERCLASSIFIER_H
#define ANOTHERCLASSIFIER_H

#include "Classifier.h"
#include <string>
#include <vector>

class AnotherClassifier : public Classifier {
private:
    // Some dummy vector as placeholder for future implementation
    // This was shown in the professor's diagram
    std::vector<int> someInternalVector;

public:
    // Constructor
    AnotherClassifier();

    // Destructor
    ~AnotherClassifier();

    // Stub implementation - just prints a message
    void train(const std::vector<double>& xValues,
        const std::vector<double>& yValues,
        const std::vector<double>& zValues,
        const std::vector<int>& labels) override;

    // Stub implementation - prints message and returns negative one
    int classify(double x, double y, double z) override;

    // Returns the name of this classifier
    std::string getClassifierName() const override;
};

#endif