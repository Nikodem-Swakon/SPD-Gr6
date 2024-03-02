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
    void HeapSort();
    class Heap
    {
    private:
        /* Private members */
        std::vector<int> m_elements;
        int m_heapSize;

        /* Private methods */

    public:
        /* Public methods */
        Heap();
        ~Heap();
        void Insert(int elem);
        int GetMaximum();
        void BuildHeap(std::vector<int> elems);
        void PrintHeap(int elemId, std::string sp = "", std::string sn = "");

        int GetLeftChildId(int elemId);
        int GetRightChildId(int elemId);
        int GetParentId(int elemId);
        void Heapify(int elemId);
        void Heapify();

    };

} // namespace Structure
#endif
