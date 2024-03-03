/*
    Binary Heap
*/
#ifndef HEAP_HPP
#define HEAP_HPP
#include <iostream>
#include <vector>
#include <string>

#define TAB "   " // fills up empty space between the left edge and the leafs
namespace Structure
{
    void HeapSort(std::vector<int> &elems);
    class Heap
    {
    protected:
        /* Protected members */
        std::vector<int> m_elements;
        int m_heapSize;

        /* Protected methods */

    public:
        /* Public methods */
        Heap();
        ~Heap();
        void Insert(int elem);
        int GetMaximum();
        void BuildHeap(std::vector<int> &elems);
        void PrintHeap(int elemId, std::string sp = "", std::string sn = "");

        int GetLeftChildId(int elemId);
        int GetRightChildId(int elemId);
        int GetParentId(int elemId);
        void HeapifyDown(int elemId);
        void Heapify(int elemId);
        void HeapSort();
        bool Empty() {return m_heapSize == 0;};
        void InserVector(std::vector<int> &elems);

    };

} // namespace Structure
#endif
