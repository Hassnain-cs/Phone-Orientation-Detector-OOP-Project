/**
 * @file UserInterface.h
 * @brief Declares the console-based user interface for the application.
 * @author Muhammad Hassnain
 * @date April 2026
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "DataPoint.h"
#include <string>
#include <vector>

 /**
  * @class UserInterface
  * @brief Handles all console input and output for the application.
  *
  * This class is responsible for menus, prompts, user messages, result display,
  * ASCII art output, and colored text formatting. It keeps presentation logic
  * separate from application and classifier logic.
  */
class UserInterface {
private:
    /**
     * @brief Clears the console screen.
     *
     * Works on both Windows and Unix-like systems.
     */
    void clearConsoleScreen() const;

public:
    /**
     * @brief Constructs a UserInterface object.
     */
    UserInterface();

    /**
     * @brief Displays the welcome banner at program startup.
     */
    void showWelcomeScreen() const;

    /**
     * @brief Displays the main menu and gets the user's selection.
     * @return Selected main menu option.
     */
    int getMainMenuChoice() const;

    /**
     * @brief Displays the classifier selection menu.
     * @return Selected classifier option.
     */
    int getClassifierChoice() const;

    /**
     * @brief Displays the input method menu for classifier input.
     * @return Selected input method option.
     */
    int getInputMethodChoice() const;

    /**
     * @brief Gets manual x, y, and z gravity input from the user.
     * @return DataPoint containing the entered gravity values.
     */
    DataPoint getManualInputFromUser() const;

    /**
     * @brief Prompts the user to enter a filename.
     * @param prompt Message shown to the user.
     * @return Filename entered by the user.
     */
    std::string askForFilename(const std::string& prompt) const;

    /**
     * @brief Displays a single prediction result.
     * @param result Classified data point.
     * @param confidence Confidence percentage for the prediction.
     */
    void showPredictionResult(const DataPoint& result, double confidence) const;

    /**
     * @brief Displays ASCII art for the predicted phone orientation.
     * @param asciiArt ASCII art string to display.
     */
    void showPhoneOrientationArt(const std::string& asciiArt) const;

    /**
     * @brief Displays a summary after batch file processing.
     * @param results Vector of classified data points.
     * @param timeInSeconds Total processing time in seconds.
     */
    void showBatchProcessingSummary(const std::vector<DataPoint>& results,
        double timeInSeconds) const;

    /**
     * @brief Displays an error message.
     * @param msg Error message text.
     */
    void showErrorMessage(const std::string& msg) const;

    /**
     * @brief Displays a success message.
     * @param msg Success message text.
     */
    void showSuccessMessage(const std::string& msg) const;

    /**
     * @brief Displays an informational message.
     * @param msg Informational message text.
     */
    void showInfoMessage(const std::string& msg) const;

    /**
     * @brief Displays a warning message.
     * @param msg Warning message text.
     */
    void showWarningMessage(const std::string& msg) const;

    /**
     * @brief Waits for the user to press Enter before continuing.
     */
    void waitForUserInput() const;

    /**
     * @brief Prints text using a specified terminal color code.
     * @param text Text to display.
     * @param colorCode ANSI color code to apply.
     */
    void printWithColor(const std::string& text, int colorCode) const;
};

#endif