#include <iostream>
#include "Inc/Heap.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    Structure::Heap heap;
    heap.BuildHeap({1,2,3,4,5,6,7});
    std::cout << "rodzic: " << heap.GetParentId(2)<< std::endl;
    std::cout << "prawe dziecko: " << heap.GetRightChildId(2)<< std::endl;
    std::cout << "lewe dziecko: " << heap.GetLeftChildId(2)<< std::endl;
    
}