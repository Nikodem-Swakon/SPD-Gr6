#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <string>
#include <algorithm> //std::sort

void extract(const std::string& line, std::vector<int>& values) {
    
    std::istringstream iss(line);
    int value;
    //iss >> value;  //skipping the first value in line
    while (iss >> value) {
        
            values.push_back(value);
            //std::cout << "Number: " << value << std::endl;
    
    }
}

//                Algorytmy sortowania           //
// Najkrótszy czas dostępności 
bool compareReleaseTimeValue(const std::vector<int>& a, const std::vector<int>& b) {
    return a[1] < b[1];
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

    std::sort(Machine.begin(), Machine.end(), compareReleaseTimeValue);
        
 // Print sorted machines
    /*
    for (const auto& machine : Machine) {
        std::cout << "Machine nr "<<machine[0]<<":  ";
        for (size_t i = 1; i < machine.size(); ++i) {
            std::cout << machine[i] << " ";
        }
        std::cout << std::endl;
    }
    */
        //Time-Graph output
        //int cooldown=0;
        int Offset=0;
        int PRE=0;
        int MID=0;
        std::cout<<"            Time-Graph          "<<std::endl;
        std::cout<<"________________________________"<<std::endl;
        for (const auto& machine : Machine) {
        
        std::cout<<"Offset:"<<Offset<<std::endl;
        std::cout << "Machine nr "<<machine[0]<<"]";

        if(Offset+PRE+MID>=machine[1]){
        //Offset=MID+PRE-machine[1];
            for(int x =0; x<MID+PRE+Offset-machine[1];x++){
            std::cout<<" ";
            } 
        Offset=MID+PRE+Offset-machine[1];
        }
        
        PRE=machine[1];
        MID=machine[2];
        
        //Offset+=machine[2];
        //cooldown =machine [3];

        if(machine[1]>0){std::cout<<"<";}
        for (int i=0;i<machine[1]-1;i++){
            std::cout<<"-";
        }
        
        for (int j=0;j<machine[2];j++){
            std::cout<<"%";
        }
        
        for(int k=0;k<machine[3]-1;k++){
            std::cout<<"-";
        }
        if(machine[3]>0){std::cout<<">";}
        std::cout << std::endl;
    }

    return 0;
}