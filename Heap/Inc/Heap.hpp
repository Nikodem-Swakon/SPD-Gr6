/*
    Binary Heap
*/
#ifndef HEAP_HPP
#define HEAP_HPP
#include <iostream>
#include <vector>

namespace Structure
{
    class Heap
    {
    private:
        /* Private members */
        std::vector<int> m_elements;
        int m_heapSize;

        /* Private methods */
        void Heapify();

    public:
        /* Public methods */
        Heap();
        ~Heap();
        void Insert();
        int GetMaximum();
        int ExtractMaximum();
        void HeapSort();
        void BuildHeap(std::vector<int> elems);


        int GetLeftChildId(int elemId);
        int GetRightChildId(int elemId);
        int GetParentId(int elemId);
    };

} // namespace Structure
#endif
