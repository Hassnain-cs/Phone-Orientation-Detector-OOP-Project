#pragma once
// Classifier.h
// Base abstract class for all phone orientation classifiers
// This class cannot be instantiated, it only defines the interface

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <string>

class Classifier {
protected:

    // Training data stored in the base class so all derived classes can access it

    std::vector<double> trainingDataX;
    std::vector<double> trainingDataY;
    std::vector<double> trainingDataZ;
    std::vector<int> trainingLabels;

public:
    // Virtual destructor for proper cleanup of derived classes

    virtual ~Classifier() {}

    // Pure virtual function, must be implemented by all derived classes
    // Takes training data and stores it for later classification

    virtual void train(const std::vector<double>& xValues,
        const std::vector<double>& yValues,
        const std::vector<double>& zValues,
        const std::vector<int>& labels) = 0;

    // Pure virtual function, must be implemented by all derived classes
    // Classifies a single sample
    // Returns the predicted orientation label (1 through 6)

    virtual int classify(double x, double y, double z) = 0;

    // Returns the name of the classifier as a string
    virtual std::string getClassifierName() const = 0;
};

#endif