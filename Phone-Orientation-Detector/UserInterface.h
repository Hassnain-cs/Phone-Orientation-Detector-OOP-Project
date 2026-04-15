// UserInterface.h
// Handles all console input and output for the application
// Demonstrates separation of concerns - UI is separate from logic

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "DataPoint.h"
#include <string>
#include <vector>

class UserInterface {
private:
    // Clears the console screen (works on both Windows and Unix)
    void clearConsoleScreen() const;

public:
    // Constructor
    UserInterface();

    // Shows the welcome banner when program starts
    void showWelcomeScreen() const;

    // Displays the main menu and gets user selection
    int getMainMenuChoice() const;

    // Shows classifier selection menu
    int getClassifierChoice() const;

    // Shows input method menu for NN classifier
    int getInputMethodChoice() const;

    // Gets manual x y z input from the user
    DataPoint getManualInputFromUser() const;

    // Asks user for a filename
    std::string askForFilename(const std::string& prompt) const;

    // Displays a single prediction result
    void showPredictionResult(const DataPoint& result, double confidence) const;

    // Shows ASCII art representation of phone orientation
    void showPhoneOrientationArt(const std::string& asciiArt) const;

    // Shows summary after processing a batch file
    void showBatchProcessingSummary(const std::vector<DataPoint>& results,
        double timeInSeconds) const;

    // Different types of messages with appropriate colors
    void showErrorMessage(const std::string& msg) const;
    void showSuccessMessage(const std::string& msg) const;
    void showInfoMessage(const std::string& msg) const;
    void showWarningMessage(const std::string& msg) const;

    // Waits for user to press enter before continuing
    void waitForUserInput() const;

    // Prints text with color for better user experience
    // Made public so Application can use it for test results
    void printWithColor(const std::string& text, int colorCode) const;
};

#endif