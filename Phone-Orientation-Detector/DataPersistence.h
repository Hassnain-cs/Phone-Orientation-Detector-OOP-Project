/**
 * @file DataPersistence.h
 * @brief Declares file input and output operations for training and result data.
 * @author Raj Bahadur Bhat
 * @date April 2026
 */

#ifndef DATAPERSISTENCE_H
#define DATAPERSISTENCE_H

#include "DataPoint.h"
#include <vector>
#include <string>

 /**
  * @class DataPersistence
  * @brief Handles reading, writing, validation, and reporting for project data files.
  *
  * This utility class provides static functions for loading training data,
  * loading unknown input samples, writing classification results, displaying
  * training statistics, and correcting invalid gravity values.
  */
class DataPersistence {
public:
    /**
     * @brief Reads labeled training or testing data from a file.
     * @param filename Name of the file to read.
     * @param outXValues Output vector for x-axis values.
     * @param outYValues Output vector for y-axis values.
     * @param outZValues Output vector for z-axis values.
     * @param outLabels Output vector for orientation labels.
     * @return Number of samples read, or -1 if the file could not be opened.
     */
    static int read(const std::string& filename,
        std::vector<double>& outXValues,
        std::vector<double>& outYValues,
        std::vector<double>& outZValues,
        std::vector<int>& outLabels);

    /**
     * @brief Reads unknown unlabeled data samples from a file.
     * @param filename Name of the file to read.
     * @return Vector of DataPoint objects built from the file contents.
     */
    static std::vector<DataPoint> read(const std::string& filename);

    /**
     * @brief Writes classification results to an output file.
     * @param filename Name of the file to write.
     * @param results Vector of classified DataPoint objects.
     * @return True if writing succeeded, otherwise false.
     */
    static bool write(const std::string& filename,
        const std::vector<DataPoint>& results);

    /**
     * @brief Displays statistics about the distribution of training labels.
     * @param labels Vector of training labels.
     */
    static void showTrainingStatistics(const std::vector<int>& labels);

    /**
     * @brief Validates and fixes data points with out-of-range gravity values.
     * @param points Vector of DataPoint objects to validate.
     * @return Number of data points that were corrected.
     */
    static int validateAndFixData(std::vector<DataPoint>& points);
};

#endif