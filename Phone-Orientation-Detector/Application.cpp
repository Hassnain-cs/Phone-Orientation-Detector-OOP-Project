// Application.cpp
// Implementation of the main application controller
// Ties together UI, FileHandler, and Classifier components

#include "Application.h"
#include "NNClassifier.h"
#include "AnotherClassifier.h"
#include "KNNClassifier.h"
#include "FileHandler.h"
#include <chrono>
#include <iostream>

Application::Application() {
    currentClassifier = nullptr;
}

void Application::initializeOrientationMappings() {
    // Set up the orientation strings for each label
    labelToOrientationMap[1] = "Face up";
    labelToOrientationMap[2] = "Face down";
    labelToOrientationMap[3] = "Portrait";
    labelToOrientationMap[4] = "Portrait upside down";
    labelToOrientationMap[5] = "Landscape left";
    labelToOrientationMap[6] = "Landscape right";

    // ASCII art for visual representation of each orientation
    labelToAsciiArtMap[1] =
        "+---------------+\n"
        "|    FACE UP    |\n"
        "|   +-------+   |\n"
        "|   | [___] |   |\n"
        "|   |  ___  |   |\n"
        "|   | |   | |   |\n"
        "|   | |___| |   |\n"
        "|   +-------+   |\n"
        "+---------------+";

    labelToAsciiArtMap[2] =
        "+---------------+\n"
        "|   FACE DOWN   |\n"
        "|   +-------+   |\n"
        "|   |       |   |\n"
        "|   |  ___  |   |\n"
        "|   | |___| |   |\n"
        "|   | [___] |   |\n"
        "|   +-------+   |\n"
        "+---------------+";

    labelToAsciiArtMap[3] =
        "+---------------+\n"
        "|   PORTRAIT    |\n"
        "|   +-------+   |\n"
        "|   | [___] |   |\n"
        "|   |  ___  |   |\n"
        "|   | |   | |   |\n"
        "|   | |___| |   |\n"
        "|   +-------+   |\n"
        "+---------------+";

    labelToAsciiArtMap[4] =
        "+---------------+\n"
        "| PORTRAIT UPS  |\n"
        "|   +-------+   |\n"
        "|   | |___| |   |\n"
        "|   | |   | |   |\n"
        "|   | |___| |   |\n"
        "|   | [___] |   |\n"
        "|   +-------+   |\n"
        "+---------------+";

    labelToAsciiArtMap[5] =
        "+---------------+\n"
        "| LANDSCAPE L   |\n"
        "| +-----------+ |\n"
        "| | [___]  ___| |\n"
        "| |       |   | |\n"
        "| |       |___| |\n"
        "| +-----------+ |\n"
        "+---------------+";

    labelToAsciiArtMap[6] =
        "+---------------+\n"
        "| LANDSCAPE R   |\n"
        "| +-----------+ |\n"
        "| | ___  [___]| |\n"
        "| | |   |      | |\n"
        "| | |___|      | |\n"
        "| +-----------+ |\n"
        "+---------------+";
}

bool Application::initialize() {
    ui.showWelcomeScreen();
    ui.showInfoMessage("Initializing Phone Orientation Detector...");

    initializeOrientationMappings();

    if (!loadTrainingDataFile()) {
        ui.showErrorMessage("Failed to load training data file.");
        ui.showInfoMessage("Make sure trainingData.txt is in the working directory.");
        return false;
    }

    ui.showSuccessMessage("Application initialized successfully.");
    ui.showInfoMessage("Training data loaded: " + std::to_string(trainLabels.size()) + " samples.");

    return true;
}

bool Application::loadTrainingDataFile() {
    int count = FileHandler::loadTrainingData("trainingData.txt", trainX, trainY, trainZ, trainLabels);

    if (count > 0) {
        FileHandler::showTrainingStatistics(trainLabels);
        return true;
    }

    return false;
}

bool Application::selectAndSetupClassifier(int choice) {
    switch (choice) {
    case 1:
        currentClassifier = std::make_unique<NNClassifier>();
        currentClassifier->train(trainX, trainY, trainZ, trainLabels);
        ui.showSuccessMessage("Nearest Neighbor classifier selected and trained.");
        return true;

    case 2:
        currentClassifier = std::make_unique<AnotherClassifier>();
        ui.showWarningMessage("AnotherClassifier is not implemented yet.");
        ui.showInfoMessage("Only printing function names will occur.");
        return false;

    case 3:
        currentClassifier = std::make_unique<KNNClassifier>();
        ui.showWarningMessage("KNNClassifier is not implemented yet.");
        ui.showInfoMessage("Only printing function names will occur.");
        return false;

    default:
        return false;
    }
}

void Application::handleManualInputMode() {
    DataPoint input = ui.getManualInputFromUser();

    // Check if gravity values are within valid range
    if (!input.areGravityValuesValid()) {
        ui.showWarningMessage("Values outside valid range [-1, 1] detected. Clamping.");
        input.clampGravityValues();
    }

    // Get prediction from classifier
    int predictedLabel = currentClassifier->classify(input.xAxis, input.yAxis, input.zAxis);

    // Get confidence if using NN classifier
    double confidence = 0.0;
    NNClassifier* nnClassifier = dynamic_cast<NNClassifier*>(currentClassifier.get());
    if (nnClassifier) {
        auto result = nnClassifier->classifyWithConfidence(input.xAxis, input.yAxis, input.zAxis);
        predictedLabel = result.first;
        confidence = result.second;
    }
    else {
        predictedLabel = currentClassifier->classify(input.xAxis, input.yAxis, input.zAxis);
        confidence = 100.0; // Default for stub classifiers
    }

    input.orientationLabel = predictedLabel;
    input.orientationName = labelToOrientationMap[predictedLabel];

    ui.showPredictionResult(input, confidence);
    ui.showPhoneOrientationArt(labelToAsciiArtMap[predictedLabel]);
}

void Application::handleFileInputMode() {
    std::string filename = ui.askForFilename("Enter data file name (example: unknownData.txt): ");

    std::vector<DataPoint> dataPoints = FileHandler::loadUnknownData(filename);

    if (dataPoints.empty()) {
        ui.showErrorMessage("No data found in file or file is empty.");
        return;
    }

    ui.showInfoMessage("Processing " + std::to_string(dataPoints.size()) + " samples...");

    // Validate and fix any out of range values
    int fixedCount = FileHandler::validateAndFixData(dataPoints);
    if (fixedCount > 0) {
        ui.showWarningMessage(std::to_string(fixedCount) + " samples were corrected to [-1, 1] range.");
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    // Classify each data point
    for (auto& dp : dataPoints) {
        dp.orientationLabel = currentClassifier->classify(dp.xAxis, dp.yAxis, dp.zAxis);
        dp.orientationName = labelToOrientationMap[dp.orientationLabel];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double processingTime = std::chrono::duration<double>(endTime - startTime).count();

    std::string outFilename = ui.askForFilename("Enter output file name (example: result.txt): ");

    if (FileHandler::saveResults(outFilename, dataPoints)) {
        ui.showSuccessMessage("Results saved to: " + outFilename);
    }
    else {
        ui.showErrorMessage("Failed to save results file.");
    }

    ui.showBatchProcessingSummary(dataPoints, processingTime);
}

void Application::runAccuracyTest() {
    ui.showInfoMessage("Running accuracy test on testingData.txt...");

    std::vector<double> testX, testY, testZ;
    std::vector<int> testLabels;

    int count = FileHandler::loadTrainingData("testingData.txt", testX, testY, testZ, testLabels);

    if (count <= 0) {
        ui.showErrorMessage("Could not load testingData.txt");
        return;
    }

    // Create and train NN classifier for testing
    NNClassifier testClassifier;
    testClassifier.train(trainX, trainY, trainZ, trainLabels);

    int correct = 0;
    for (size_t i = 0; i < testX.size(); i++) {
        int predicted = testClassifier.classify(testX[i], testY[i], testZ[i]);
        if (predicted == testLabels[i]) {
            correct++;
        }
    }

    double accuracy = (static_cast<double>(correct) / testX.size()) * 100.0;

    std::cout << std::endl;
    ui.printWithColor("+--------------------------------------+\n", 36);
    ui.printWithColor("|           TEST RESULTS               |\n", 36);
    ui.printWithColor("+--------------------------------------+\n", 36);
    std::cout << "  Correct predictions: " << correct << " out of " << testX.size() << "\n";
    std::cout << "  Accuracy: ";

    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.2f", accuracy);
    ui.printWithColor(std::string(buffer) + "%\n", 32);
    ui.printWithColor("+--------------------------------------+\n", 36);
}

void Application::run() {
    bool running = true;

    while (running) {
        int mainChoice = ui.getMainMenuChoice();

        switch (mainChoice) {
        case 1: {
            int classifierChoice = ui.getClassifierChoice();
            selectAndSetupClassifier(classifierChoice);

            if (classifierChoice == 1) {
                int inputChoice = ui.getInputMethodChoice();

                if (inputChoice == 1) {
                    handleManualInputMode();
                }
                else {
                    handleFileInputMode();
                }
            }
            else {
                std::cout << std::endl;
                // Call classify once to trigger the stub message
                currentClassifier->classify(0, 0, 0);
                ui.showInfoMessage("This classifier cannot process data.");
                ui.showInfoMessage("Please select Nearest Neighbor classifier for actual predictions.");
            }
            ui.waitForUserInput();
            break;
        }

        case 2:
            runAccuracyTest();
            ui.waitForUserInput();
            break;

        case 3:
            ui.showInfoMessage("Phone Orientation Detector Help");
            ui.showInfoMessage("-------------------------------------------");
            ui.showInfoMessage("Step 1: Choose Nearest Neighbor classifier");
            ui.showInfoMessage("Step 2: Select input method (manual or file)");
            ui.showInfoMessage("Step 3: For manual, enter x, y, z values");
            ui.showInfoMessage("Step 4: For file, provide filename like unknownData.txt");
            ui.showInfoMessage("Step 5: Results will be shown and saved to result.txt");
            ui.showInfoMessage("-------------------------------------------");
            ui.showInfoMessage("Gravity values must be between -1.0 and 1.0");
            ui.waitForUserInput();
            break;

        case 4:
            ui.showInfoMessage("Thank you for using Phone Orientation Detector.");
            ui.showInfoMessage("Exiting application...");
            running = false;
            break;
        }
    }
}