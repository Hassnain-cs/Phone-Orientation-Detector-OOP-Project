/**
 * @file UserInterface.cpp
 * @brief Implements the console-based user interface.
 * @author Muhammad Hassnain
 * @date April 2026
 */

#include "UserInterface.h"

 // Define NOMINMAX before including windows.h to prevent max/min macro conflicts
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <cstdlib>
#endif

#include <iostream>
#include <limits>
#include <iomanip>
#include <map>

UserInterface::UserInterface() {
    // Nothing to initialize
}

void UserInterface::clearConsoleScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UserInterface::printWithColor(const std::string& text, int colorCode) const {
    // ANSI escape codes for terminal colors
    // 31=red, 32=green, 33=yellow, 34=blue, 35=purple, 36=cyan
    std::cout << "\033[" << colorCode << "m" << text << "\033[0m";
}

void UserInterface::showWelcomeScreen() const {
    clearConsoleScreen();
    std::cout << std::endl;
    printWithColor("============================================================\n", 36);
    printWithColor("     PHONE ORIENTATION DETECTOR                              \n", 32);
    printWithColor("     OOP Course Project - PROG71020                          \n", 32);
    printWithColor("============================================================\n", 36);
    std::cout << std::endl;
}

int UserInterface::getMainMenuChoice() const {
    int choice;

    std::cout << std::endl;
    printWithColor("+---------------------------+\n", 36);
    printWithColor("|        MAIN MENU          |\n", 33);
    printWithColor("+---------------------------+\n", 36);
    std::cout << "| 1. Select Classifier      |\n";
    std::cout << "| 2. Run Test Suite         |\n";
    std::cout << "| 3. View Help              |\n";
    std::cout << "| 4. Exit                   |\n";
    printWithColor("+---------------------------+\n", 36);
    std::cout << "Enter your choice (1-4): ";

    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        printWithColor("Invalid choice. Please enter a number between 1 and 4: ", 31);
    }

    return choice;
}

int UserInterface::getClassifierChoice() const {
    int choice;

    std::cout << std::endl;
    printWithColor("+--------------------------------+\n", 36);
    printWithColor("|      SELECT CLASSIFIER         |\n", 33);
    printWithColor("+--------------------------------+\n", 36);
    printWithColor("| 1. Nearest Neighbor (NN)       |\n", 32);
    std::cout << "| 2. Another Classifier          |\n";
    std::cout << "| 3. KNN Classifier              |\n";
    printWithColor("+--------------------------------+\n", 36);
    std::cout << "Enter your choice (1-3): ";

    while (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        printWithColor("Invalid choice. Please enter 1, 2, or 3: ", 31);
    }

    return choice;
}

int UserInterface::getInputMethodChoice() const {
    int choice;

    std::cout << std::endl;
    printWithColor("+--------------------------------+\n", 36);
    printWithColor("|      SELECT INPUT METHOD       |\n", 33);
    printWithColor("+--------------------------------+\n", 36);
    std::cout << "| 1. Enter sample data (x,y,z)   |\n";
    std::cout << "| 2. Enter file name             |\n";
    printWithColor("+--------------------------------+\n", 36);
    std::cout << "Enter your choice (1-2): ";

    while (!(std::cin >> choice) || choice < 1 || choice > 2) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        printWithColor("Invalid choice. Please enter 1 or 2: ", 31);
    }

    return choice;
}

DataPoint UserInterface::getManualInputFromUser() const {
    double x, y, z;

    std::cout << std::endl;
    printWithColor("--- Enter Gravity Values ---\n", 34);
    showInfoMessage("Values must be between -1.0 and 1.0");
    std::cout << std::endl;

    std::cout << "Enter X value: ";
    std::cin >> x;

    std::cout << "Enter Y value: ";
    std::cin >> y;

    std::cout << "Enter Z value: ";
    std::cin >> z;

    return DataPoint(x, y, z, -1);
}

std::string UserInterface::askForFilename(const std::string& prompt) const {
    std::string filename;
    std::cout << prompt;
    std::cin >> filename;
    return filename;
}

void UserInterface::showPredictionResult(const DataPoint& result, double confidence) const {
    std::cout << std::endl;
    printWithColor("+--------------------------------------+\n", 35);
    printWithColor("|            PREDICTION                |\n", 35);
    printWithColor("+--------------------------------------+\n", 35);

    std::cout << "  Input values: (";
    std::cout << std::fixed << std::setprecision(5);
    std::cout << result.xAxis << ", " << result.yAxis << ", " << result.zAxis << ")\n";

    std::cout << "  Predicted label: " << result.orientationLabel << "\n";

    std::cout << "  Orientation: ";
    printWithColor(result.orientationName, 32);
    std::cout << std::endl;

    std::cout << "  Confidence: ";

    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.2f", confidence);
    std::string confidenceStr(buffer);
    printWithColor(confidenceStr + "%", 34);
    std::cout << std::endl;

    printWithColor("+--------------------------------------+\n", 35);
}

void UserInterface::showPhoneOrientationArt(const std::string& asciiArt) const {
    std::cout << std::endl;
    printWithColor(asciiArt + "\n", 36);
}

void UserInterface::showBatchProcessingSummary(const std::vector<DataPoint>& results,
    double timeInSeconds) const {
    std::map<int, int> orientationCounts;

    for (const auto& dp : results) {
        orientationCounts[dp.orientationLabel]++;
    }

    std::cout << std::endl;
    printWithColor("+======================================+\n", 32);
    printWithColor("|         BATCH PROCESSING SUMMARY      |\n", 32);
    printWithColor("+======================================+\n", 32);

    std::cout << "  Total samples processed: " << results.size() << "\n";
    std::cout << "  Time taken: " << std::fixed << std::setprecision(4)
        << timeInSeconds << " seconds\n";

    std::cout << std::endl;
    printWithColor("  Orientation Distribution:\n", 33);

    std::map<int, std::string> orientationNames = {
        {1, "Face up"},
        {2, "Face down"},
        {3, "Portrait"},
        {4, "Portrait upside down"},
        {5, "Landscape left"},
        {6, "Landscape right"}
    };

    for (int i = 1; i <= 6; i++) {
        if (orientationCounts[i] > 0) {
            std::cout << "    " << orientationNames[i] << ": "
                << orientationCounts[i] << " samples\n";
        }
    }

    printWithColor("+======================================+\n", 32);
}

void UserInterface::showErrorMessage(const std::string& msg) const {
    printWithColor("[ERROR] ", 31);
    std::cout << msg << std::endl;
}

void UserInterface::showSuccessMessage(const std::string& msg) const {
    printWithColor("[SUCCESS] ", 32);
    std::cout << msg << std::endl;
}

void UserInterface::showInfoMessage(const std::string& msg) const {
    printWithColor("[INFO] ", 34);
    std::cout << msg << std::endl;
}

void UserInterface::showWarningMessage(const std::string& msg) const {
    printWithColor("[WARNING] ", 33);
    std::cout << msg << std::endl;
}

void UserInterface::waitForUserInput() const {
    std::cout << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cin.get();
}