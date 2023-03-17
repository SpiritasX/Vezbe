/*
Uneti 5 celih brojeva sa standardnog ulaza.
Korišćenjem STL algoritma sortirati brojeve u rastućem redosledu.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> input;

    int temp;

    for (int i = 0; i < 5; i++)
    {
        std::cin >> temp;
        input.push_back(temp);
    }

    std::sort(input.begin(), input.end());
    
    for (int i : input)
        std::cout << i << " ";
    
    std::cout << std::endl;

    return 0;
}
