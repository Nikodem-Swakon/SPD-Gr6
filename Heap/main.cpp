#include <iostream>
#include "Inc/Heap.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    Structure::Heap heap;
    heap.BuildHeap({100, 56, 89, 2 , 43, 33, 1, 5, 2});
    std::cout << "parent " << heap.GetParentId(2)<< std::endl;
    std::cout << "right child: " << heap.GetRightChildId(2)<< std::endl;
    std::cout << "left child: " << heap.GetLeftChildId(2)<< std::endl;

    std::cout << std::endl << "Heap" << std::endl;
    heap.PrintHeap(0);

    std::cout << std::endl << "Element instert" << std::endl;
    heap.Insert(0);
    heap.PrintHeap(0);

    std::cout << std::endl << "Heapify" << std::endl;

    heap.Heapify();
    heap.PrintHeap(0);

}