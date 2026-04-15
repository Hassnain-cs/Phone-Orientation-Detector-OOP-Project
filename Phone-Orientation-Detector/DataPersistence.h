// DataPersistence.h
// Handles all reading and writing of data files
// Professor requirement: class named DataPersistence with read() and write() methods

#ifndef DATAPERSISTENCE_H
#define DATAPERSISTENCE_H

#include "DataPoint.h"
#include <vector>
#include <string>

class DataPersistence {
public:
    // Reads the training data file and populates the vectors
    // Returns the number of samples read, or -1 on error
    static int read(const std::string& filename,
        std::vector<double>& outXValues,
        std::vector<double>& outYValues,
        std::vector<double>& outZValues,
        std::vector<int>& outLabels);

    // Reads a file containing unknown samples without labels
    // Returns a vector of DataPoint objects with label set to -1
    static std::vector<DataPoint> read(const std::string& filename);

    // Writes classification results to an output file
    // Returns true if writing was successful, false otherwise
    static bool write(const std::string& filename,
        const std::vector<DataPoint>& results);

    // Displays statistics about the training data distribution
    static void showTrainingStatistics(const std::vector<int>& labels);

    // Checks data points for invalid values and fixes them
    // Returns the number of points that were corrected
    static int validateAndFixData(std::vector<DataPoint>& points);
};

#endif