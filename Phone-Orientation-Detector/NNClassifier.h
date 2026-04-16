/**
 * @file NNClassifier.h
 * @brief Defines the Nearest Neighbor classifier.
 * @author Fabio Bustamante Romillo
 * @date April 2026
 */

#pragma once
#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include "Classifier.h"
#include <string>
#include <utility>

 /**
  * @class NNClassifier
  * @brief Concrete classifier that uses the nearest neighbor algorithm.
  *
  * This classifier compares an unknown sample against all stored training samples
  * using Euclidean distance and returns the label of the closest match.
  */
class NNClassifier : public Classifier {
private:
    /**
     * @brief Calculates Euclidean distance between two 3D gravity points.
     * @param x1 First point x value.
     * @param y1 First point y value.
     * @param z1 First point z value.
     * @param x2 Second point x value.
     * @param y2 Second point y value.
     * @param z2 Second point z value.
     * @return Euclidean distance between the two points.
     */
    double calculateEuclideanDistance(double x1, double y1, double z1,
        double x2, double y2, double z2) const;

public:
    /**
     * @brief Constructs an NNClassifier object.
     */
    NNClassifier();

    /**
     * @brief Destroys an NNClassifier object.
     */
    ~NNClassifier();

    /**
     * @brief Stores training data for nearest neighbor classification.
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
     * @brief Classifies a gravity sample using nearest neighbor search.
     * @param x X-axis gravity value.
     * @param y Y-axis gravity value.
     * @param z Z-axis gravity value.
     * @return Predicted orientation label.
     */
    int classify(double x, double y, double z) override;

    /**
     * @brief Returns the name of this classifier.
     * @return Classifier name as a string.
     */
    std::string getClassifierName() const override;

    /**
     * @brief Classifies a sample and estimates a confidence percentage.
     * @param x X-axis gravity value.
     * @param y Y-axis gravity value.
     * @param z Z-axis gravity value.
     * @return A pair containing the predicted label and confidence percentage.
     */
    std::pair<int, double> classifyWithConfidence(double x, double y, double z);
};

#endif