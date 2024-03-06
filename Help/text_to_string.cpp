#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>


void extract(const std::string& line) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
        
            std::cout << "Number: " << word << std::endl;
    
    }
}


int main() {
    
    std::ifstream file("text.txt"); // Open the input file
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;                     // For skipping first line 
    bool isFirstLine = true;              // For skipping first line 
    while (std::getline(file, line)) {    // Read file line by line
        if (isFirstLine) {                // For skipping first line  
            isFirstLine = false;          // For skipping first line 
            continue;                     // Skip the first line
        }
        extract(line);      // Extract text and numbers from the line
    }

    file.close(); // Close the file
    return 0;
}