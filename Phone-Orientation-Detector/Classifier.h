/**
 * @file Classifier.h
 * @brief Defines the abstract base class for all phone orientation classifiers.
 * @author Fabio Bustamante Romillo, Muhammad Hassnain, and Raj Bahadur Bhat
 * @date April 2026
 */

#pragma once
#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <string>

 /**
  * @class Classifier
  * @brief Abstract base class that defines the common interface for all classifiers.
  *
  * This class stores training data and forces all derived classifier classes
  * to implement training, classification, and classifier naming behavior.
  * It cannot be instantiated directly because it contains pure virtual methods.
  */
class Classifier {
protected:
    /** @brief Training x-axis gravity values. */
    std::vector<double> trainingDataX;

    /** @brief Training y-axis gravity values. */
    std::vector<double> trainingDataY;

    /** @brief Training z-axis gravity values. */
    std::vector<double> trainingDataZ;

    /** @brief Training labels associated with the gravity samples. */
    std::vector<int> trainingLabels;

public:
    /**
     * @brief Virtual destructor for safe polymorphic cleanup.
     */
    virtual ~Classifier() {}

    /**
     * @brief Stores training data for the classifier.
     * @param xValues Vector of x-axis gravity values.
     * @param yValues Vector of y-axis gravity values.
     * @param zValues Vector of z-axis gravity values.
     * @param labels Vector of orientation labels corresponding to the samples.
     */
    virtual void train(const std::vector<double>& xValues,
        const std::vector<double>& yValues,
        const std::vector<double>& zValues,
        const std::vector<int>& labels) = 0;

    /**
     * @brief Predicts the orientation label for a single gravity sample.
     * @param x X-axis gravity value.
     * @param y Y-axis gravity value.
     * @param z Z-axis gravity value.
     * @return Predicted orientation label.
     */
    virtual int classify(double x, double y, double z) = 0;

    /**
     * @brief Returns the name of the classifier.
     * @return Classifier name as a string.
     */
    virtual std::string getClassifierName() const = 0;
};

#endif