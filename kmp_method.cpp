#include <iostream>
#include <string>

using namespace std;


void computeLPSArray(string pat, int M, int lps[])
{
    int len = 0;
    lps[0] = 0;                 

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    cout << "LPS array: ";
    for (int i = 0; i < M; i++) {
        cout << lps[i] << " ";
    }
    cout << endl;
}

void KMPSearch(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();

    int lps[M];
    computeLPSArray(pat, M, lps);

    int i = 0;  
    int j = 0;  
    bool found = false;
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            cout << "Found pattern at index: " << i - j << endl;
            j = lps[j - 1];
            found=true;
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    if (!found)
        cout << "Pattern not found in the text." << endl;
}

int main()
{
    string txt, pat;

    cout << "Enter the text: ";
    getline(cin, txt);

    cout << "Enter the pattern: ";
    getline(cin, pat);

    KMPSearch(pat, txt);

    return 0;
}
