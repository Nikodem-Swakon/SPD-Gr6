#include <iostream>
#include "Inc/Heap.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    Structure::Heap heap;
    heap.BuildHeap({1,2,3,4,5,6,7,8,9,10,11});
    std::cout << "parent " << heap.GetParentId(2)<< std::endl;
    std::cout << "right child: " << heap.GetRightChildId(2)<< std::endl;
    std::cout << "left child: " << heap.GetLeftChildId(2)<< std::endl;

    std::cout << std::endl << "Heap" << std::endl;
    heap.PrintHeap(0);

    std::cout << std::endl << "Dodanie lementu" << std::endl;
    heap.Insert(0);
    heap.PrintHeap(0);

}