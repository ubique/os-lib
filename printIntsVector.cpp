#include <vector>
#include <iostream>

void printIntsVector(std::vector<int>& myVector)
{
    for (int x : myVector)
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}