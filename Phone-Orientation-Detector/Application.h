#pragma once
// Application.h
// Main controller class that ties everything together
// Demonstrates composition - contains instances of other classes

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Classifier.h"
#include "UserInterface.h"
#include <memory>
#include <vector>
#include <map>

class Application {
private:
    // User interface object for all console interaction
    UserInterface ui;

    // Maps label numbers to orientation strings
    std::map<int, std::string> labelToOrientationMap;

    // Maps label numbers to ASCII art representations
    std::map<int, std::string> labelToAsciiArtMap;

    // Current active classifier (uses polymorphism)
    std::unique_ptr<Classifier> currentClassifier;

    // Training data storage
    std::vector<double> trainX, trainY, trainZ;
    std::vector<int> trainLabels;

    // Private helper methods
    bool loadTrainingDataFile();
    bool selectAndSetupClassifier(int choice);
    void handleManualInputMode();
    void handleFileInputMode();
    void runAccuracyTest();
    void initializeOrientationMappings();

public:
    // Constructor
    Application();

    // Sets up the application, returns false if initialization fails
    bool initialize();

    // Main program loop
    void run();
};

#endif