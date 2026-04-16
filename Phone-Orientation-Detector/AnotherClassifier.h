/**
 * @file AnotherClassifier.h
 * @brief Defines a placeholder classifier for future extension.
 * @author Fabio Bustamante Romillo
 * @date April 2026
 */

#pragma once
#ifndef ANOTHERCLASSIFIER_H
#define ANOTHERCLASSIFIER_H

#include "Classifier.h"
#include <string>
#include <vector>

 /**
  * @class AnotherClassifier
  * @brief Placeholder classifier that demonstrates future extensibility.
  *
  * This class is not fully implemented yet. It exists to show how new
  * classifier types can be added to the system through inheritance.
  */
class AnotherClassifier : public Classifier {
private:
    /**
     * @brief Placeholder internal vector for possible future implementation.
     */
    std::vector<int> someInternalVector;

public:
    /**
     * @brief Constructs an AnotherClassifier object.
     */
    AnotherClassifier();

    /**
     * @brief Destroys an AnotherClassifier object.
     */
    ~AnotherClassifier();

    /**
     * @brief Placeholder training function for this classifier.
     * @param xValues Vector of x-axis training values.
     * @param yValues Vector of y-axis training values.
     * @param zValues Vector of z-axis training values.
     * @param labels Vector of training labels.
     */
    void train(const std::vector<double>& xValues,
        const std::vector<double>& yValues,
        const std::vector<double>& zValues,
        const std::vector<int>& labels) override;

    /**
     * @brief Placeholder classify function for this classifier.
     * @param x X-axis gravity value.
     * @param y Y-axis gravity value.
     * @param z Z-axis gravity value.
     * @return Placeholder label value.
     */
    int classify(double x, double y, double z) override;

    /**
     * @brief Returns the name of this classifier.
     * @return Classifier name as a string.
     */
    std::string getClassifierName() const override;
};

#endif