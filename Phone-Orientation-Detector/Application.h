/**
 * @file Application.h
 * @brief Declares the main controller class for the Phone Orientation Detector.
 * @author Muhammad Hassnain
 * @date April 2026
 */

#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Classifier.h"
#include "UserInterface.h"
#include <memory>
#include <vector>
#include <map>

 /**
  * @class Application
  * @brief Main controller class that coordinates the program workflow.
  *
  * This class ties together the user interface, classifier selection,
  * training data loading, manual and file-based input modes, prediction,
  * and testing features.
  */
class Application {
private:
    /** @brief User interface object used for console interaction. */
    UserInterface ui;

    /** @brief Maps numeric labels to readable phone orientation names. */
    std::map<int, std::string> labelToOrientationMap;

    /** @brief Maps numeric labels to ASCII art phone orientation drawings. */
    std::map<int, std::string> labelToAsciiArtMap;

    /**
     * @brief Pointer to the currently selected classifier.
     *
     * Uses polymorphism so different classifier types can be used through
     * the same base class interface.
     */
    std::unique_ptr<Classifier> currentClassifier;

    /** @brief Training x-axis values. */
    std::vector<double> trainX;

    /** @brief Training y-axis values. */
    std::vector<double> trainY;

    /** @brief Training z-axis values. */
    std::vector<double> trainZ;

    /** @brief Training orientation labels. */
    std::vector<int> trainLabels;

    /**
     * @brief Loads the training data file into memory.
     * @return True if the training data was loaded successfully, otherwise false.
     */
    bool loadTrainingDataFile();

    /**
     * @brief Selects and sets up the classifier based on the user's choice.
     * @param choice Numeric menu choice for classifier selection.
     * @return True if the classifier was set up for use, otherwise false.
     */
    bool selectAndSetupClassifier(int choice);

    /**
     * @brief Handles manual x, y, z input mode for one prediction.
     */
    void handleManualInputMode();

    /**
     * @brief Handles file input mode for batch prediction.
     */
    void handleFileInputMode();

    /**
     * @brief Runs the accuracy test using testing data.
     */
    void runAccuracyTest();

    /**
     * @brief Initializes label-to-name and label-to-ASCII-art mappings.
     */
    void initializeOrientationMappings();

public:
    /**
     * @brief Constructs an Application object.
     */
    Application();

    /**
     * @brief Initializes the application before the main run loop begins.
     * @return True if initialization succeeds, otherwise false.
     */
    bool initialize();

    /**
     * @brief Starts the main program loop.
     */
    void run();
};

#endif