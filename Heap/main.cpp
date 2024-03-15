#include <iostream>
#include "Inc/Heap.hpp"

int main()
{
    std::cout << "Main with mannual tests." << std::endl;

    Structure::Heap<int> heap;
    heap.BuildHeap({1, 56, 89, 2 , 43, 33, 1, 5, 10});
    std::cout << "parent " << heap.GetParentId(2)<< std::endl;
    std::cout << "right child: " << heap.GetRightChildId(2)<< std::endl;
    std::cout << "left child: " << heap.GetLeftChildId(2)<< std::endl;

    std::cout << std::endl << "Heap" << std::endl;
    heap.PrintHeap(0);

    std::cout << "Max elem " << heap.GetMaximum() << std::endl;

    std::cout << std::endl << "Element instert 0" << std::endl;
    heap.Insert(0);
    heap.PrintHeap(0);

    std::cout << std::endl << "Heapify" << std::endl;

    heap.PrintHeap(0);
    std::vector<int> vec{1,4,3,2,2,3,5,4,3};
    Structure::HeapSort(vec);
    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;


}