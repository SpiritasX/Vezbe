/*
Napraviti funkciju:
	
vector<int> min_n(const vector<int>& v,	int n);

Ova funkcija vraća vektor koji sadrži n najmanjih elemenata iz vektora v.
Podrazumeva se: v.size()>=n
*/

#include <iostream>
#include <vector>

std::vector<int> min_n(const std::vector<int>& v, int n)
{
    std::vector<int> v_min;
    std::vector<int> temp = v;

    for (int i = 0; i < n; i++)
    {
        auto min = temp.begin();
        for (auto it = temp.begin() + 1; it != temp.end(); it++)
            if (*it < *min)
                min = it;
        
        v_min.push_back(*min);
        temp.erase(min);
    }

    return v_min;
}

int main()
{
    std::vector<int> v = { 1, 5, 3, 4, 9, 1, 2, 3 };

    v = min_n(v, 4);

    for (int i : v)
        std::cout << i << " ";
    
    std::cout << std::endl;

    return 0;
}
