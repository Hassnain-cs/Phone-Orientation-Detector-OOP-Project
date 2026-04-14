# Phone Orientation Detector

## PROG71020 - Object Oriented Programming Course Project

### Project Overview

This application detects a smartphone's physical orientation by analyzing 3D gravity vector data. The system uses a Nearest Neighbor (NN) classifier trained on labeled sensor data to predict one of six possible phone orientations.

### Orientations Detected

| Label | Orientation |
|-------|-------------|
| 1 | Face up |
| 2 | Face down |
| 3 | Portrait |
| 4 | Portrait upside down |
| 5 | Landscape left |
| 6 | Landscape right |

### Features

- Reads training data from text files
- Implements Nearest Neighbor classification algorithm
- Provides confidence percentage for each prediction
- Supports both manual input and batch file processing
- Color coded console interface for better user experience
- ASCII art visualization of detected orientations
- Extensible architecture for adding new classifiers

### Class Structure

```mermaid
classDiagram
    class Classifier {
        #vector~double~ trainingDataX
        #vector~double~ trainingDataY
        #vector~double~ trainingDataZ
        #vector~int~ trainingLabels
        +train(x, y, z, labels)* void
        +classify(x, y, z)* int
        +getClassifierName()* string
    }
    
    class NNClassifier {
        -calculateEuclideanDistance() double
        +train(x, y, z, labels) void
        +classify(x, y, z) int
        +classifyWithConfidence() pair
        +getClassifierName() string
    }
    
    class AnotherClassifier {
        -someInternalVector vector~int~
        +train(x, y, z, labels) void
        +classify(x, y, z) int
        +getClassifierName() string
    }
    
    class KNNClassifier {
        +train(x, y, z, labels) void
        +classify(x, y, z) int
        +getClassifierName() string
    }
    
    class DataPoint {
        +xAxis double
        +yAxis double
        +zAxis double
        +orientationLabel int
        +orientationName string
        +areGravityValuesValid() bool
        +clampGravityValues() void
        +convertToString() string
    }
    
    class FileHandler {
        +loadTrainingData() int
        +loadUnknownData() vector
        +saveResults() bool
        +showTrainingStatistics() void
        +validateAndFixData() int
    }
    
    class UserInterface {
        -clearConsoleScreen() void
        -printWithColor() void
        +showWelcomeScreen() void
        +getMainMenuChoice() int
        +showPredictionResult() void
        +showPhoneOrientationArt() void
    }
    
    class Application {
        -ui UserInterface
        -labelToOrientationMap map
        -labelToAsciiArtMap map
        -currentClassifier unique_ptr~Classifier~
        +initialize() bool
        +run() void
    }
    
    Classifier <|-- NNClassifier
    Classifier <|-- AnotherClassifier
    Classifier <|-- KNNClassifier
    Application *-- UserInterface
    Application o-- Classifier
    FileHandler ..> DataPoint
    UserInterface ..> DataPoint
