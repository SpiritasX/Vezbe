/*
Uneti 5 celih brojeva sa standardnog ulaza.
Korišćenjem STL algoritma sortirati brojeve u rastućem redosledu.
*/

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> input;

    int temp;

    for (int i = 0; i < 5; i++)
    {
        std::cin >> temp;
        input.push_back(temp);
    }

    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 5; j++)
            if (input.at(i) > input.at(j))
                std::swap(input.at(i), input.at(j));
    
    for (int i : input)
        std::cout << i << " ";
    
    std::cout << std::endl;

    return 0;
}
