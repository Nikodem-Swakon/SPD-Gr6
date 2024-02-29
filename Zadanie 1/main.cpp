#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <string>

void extract(const std::string& line, std::vector<int>& values) {
    
    std::istringstream iss(line);
    int value;
    iss >> value;  //skipping the first value in line
    while (iss >> value) {
        
            values.push_back(value);
            //std::cout << "Number: " << value << std::endl;
    
    }
}


int main() {
    
    std::ifstream file("text.txt");       // Open the input file
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> Machine;  //vector of vectors

    std::string line;                     // For skipping first line 
    bool isFirstLine = true;              // For skipping first line 
    //int machnie_nr = 0;                   // Number of lines used for number of machine numbers
    //int numColumns = 0;
    while (std::getline(file, line)) {    // Read file line by line
    
    
        if (isFirstLine) {                // For skipping first line  
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                //++numColumns;
            }
            isFirstLine = false;          // For skipping first line 
            continue;                     // Skip the first line
        }
        //++machnie_nr;                     // Machine number (line nr - 1)
        //std::cout<<(machine_nr)<<std::endl;
        //std::cout<<(numColumns)<<std::endl;
        std::vector<int> values;
        extract(line, values);                    // Extract numbers from the line
        Machine.push_back(values);
    }

    file.close(); 

        
        for (size_t i = 0; i < Machine.size(); ++i) {
        std::cout << "Machine_nr" << i + 1 << " = ";
        for (int value : Machine[i]) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}