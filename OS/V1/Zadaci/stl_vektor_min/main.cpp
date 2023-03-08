/* 
Napraviti funkciju:
	
vector<int> min(const vector<int>& a, const vector<int>& b);

Ova funkcija vraća vektor koji sadrži minimume korespodentnih elemenata vektora a i b.
Npr: r[0]=min(a[0],b[0]), r[1]=...
Podrazumeva se: a.size()==b.size()
*/

#include <iostream>
#include <vector>

std::vector<int> min(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> v_min;
    
    v_min.push_back(*(a.begin()) < *(b.begin()) ? *(a.begin()) : *(b.begin()));
    v_min.push_back(*(a.begin() + 1) < *(b.begin() + 1) ? *(a.begin() + 1) : *(b.begin() + 1));

    // for (auto it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    //     v_min.push_back(*it1 < *it2 ? *it1 : *it2);
    
    return v_min;
}

int main()
{
    std::vector<int> a = { 2, 5 };
    std::vector<int> b = { 4, 3 };

    std::vector<int> c = min(a, b);

    std::cout << *(c.begin()) << " " << *(c.begin() + 1) << std::endl;

    return 0;
}
