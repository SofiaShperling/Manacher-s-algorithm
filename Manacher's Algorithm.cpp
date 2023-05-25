#include <iostream>
#include <vector>

using namespace std;

int max_element(vector<int> A, int& max, int& i_max)
{
    int n = A.size();
    max = A[0];
    i_max = 0;
    for (int i = 1; i < n; i++)
        if (A[i] > max)
        {
            max = A[i];
            i_max = i;
        }
    return 0;
}

string longestPalindrome(string s)
{
    string t;
    t.push_back('#');
    for (int i = 0; i < s.size(); i++)
    {
        t.push_back(s[i]);
        t.push_back('#');
    }

    swap(s, t);
    int n = s.size();
    vector<int> radiuses(n);

    // Manacher's Algorithm
    int l = 0, r = -1;
    for (int i = 0; i < n; i++)
    {
        int k;
        if (i > r)
            k = 1;
        else
            k = min(radiuses[i], r - l);

        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k])
            k++;

        radiuses[i] = k;

        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }


    int best_center;
    int max_radius;

    max_element(radiuses, best_center, max_radius);

    string answer_manacher = s.substr(best_center - (max_radius + 1), 2 * max_radius);

    string answer;
    for (auto i : answer_manacher)
        if (i != '#')
            answer.push_back(i);
    return answer;
}

int main()
{
    string initial_palindrom = "fgfgfgafg";
    string logest_palindrom = longestPalindrome(initial_palindrom);
    cout << "Longest palindrome in " << initial_palindrom << " is " << logest_palindrom;
}