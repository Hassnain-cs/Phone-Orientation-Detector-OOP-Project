// AnotherClassifier.cpp
// Stub implementation for a future classifier

#include "AnotherClassifier.h"
#include <iostream>

AnotherClassifier::AnotherClassifier() {
}

AnotherClassifier::~AnotherClassifier() {
}

void AnotherClassifier::train(const std::vector<double>& xValues,
    const std::vector<double>& yValues,
    const std::vector<double>& zValues,
    const std::vector<int>& labels) {
    std::cout << std::endl;
    std::cout << "AnotherClassifier::train() was called" << std::endl;
    std::cout << "This classifier is not implemented yet." << std::endl;
    std::cout << "Please select the Nearest Neighbor classifier instead." << std::endl;
}

int AnotherClassifier::classify(double x, double y, double z) {
    std::cout << std::endl;
    std::cout << "AnotherClassifier::classify() was called" << std::endl;
    std::cout << "This classifier is not implemented yet." << std::endl;
    std::cout << "Please select the Nearest Neighbor classifier instead." << std::endl;
    return -1;
}

std::string AnotherClassifier::getClassifierName() const {
    return "Another Classifier (Not Implemented)";
}