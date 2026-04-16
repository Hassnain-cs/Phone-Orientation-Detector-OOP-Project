/**
 * @file KNNClassifier.cpp
 * @brief Implements the placeholder K-Nearest Neighbor classifier.
 * @author 
 * @date April 2026
 */

#include "KNNClassifier.h"
#include <iostream>

KNNClassifier::KNNClassifier() {
}

KNNClassifier::~KNNClassifier() {
}

void KNNClassifier::train(const std::vector<double>& xValues,
    const std::vector<double>& yValues,
    const std::vector<double>& zValues,
    const std::vector<int>& labels) {
    std::cout << std::endl;
    std::cout << "KNNClassifier::train() was called" << std::endl;
    std::cout << "This classifier is not implemented yet." << std::endl;
    std::cout << "Please select the Nearest Neighbor classifier instead." << std::endl;
}

int KNNClassifier::classify(double x, double y, double z) {
    std::cout << std::endl;
    std::cout << "KNNClassifier::classify() was called" << std::endl;
    std::cout << "This classifier is not implemented yet." << std::endl;
    std::cout << "Please select the Nearest Neighbor classifier instead." << std::endl;
    return -1;
}

std::string KNNClassifier::getClassifierName() const {
    return "K-Nearest Neighbor Classifier (Not Implemented)";
}