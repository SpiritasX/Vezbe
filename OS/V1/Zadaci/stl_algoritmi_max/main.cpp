/*
Korisnik treba da unese 5 celih brojeva koristeći tastaturu (standardni ulaz).
Korišćenjem STL algoritma, među tih 5 brojeva potrebno je pronaći najveći.
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

    int max = *(input.begin());

    for (int i : input)
        if (i > max)
            max = i;
    
    std::cout << max;

    return 0;
}
