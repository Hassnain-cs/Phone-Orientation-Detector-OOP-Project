// main.cpp
// Entry point for the Phone Orientation Detector application
// This program uses machine learning to detect phone orientation from gravity data

#include "Application.h"
#include <iostream>

int main() {
    try {
        Application app;

        if (!app.initialize()) {
            std::cout << std::endl;
            std::cout << "Press Enter to exit...";
            std::cin.get();
            return 1;
        }

        app.run();

    }
    catch (const std::exception& e) {
        std::cerr << std::endl;
        std::cerr << "[FATAL ERROR] An unexpected error occurred:" << std::endl;
        std::cerr << e.what() << std::endl;
        std::cout << std::endl;
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    return 0;
}