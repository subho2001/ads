#include <iostream>
#include <string> 

using namespace std;

int main() {
    string txt;
    string pat;

    cout << "Enter the text: ";
    getline(cin, txt); 

    cout << "Enter the pattern to search: ";
    getline(cin, pat); 

    int M = pat.length();
    int N = txt.length();

    bool patternFound = false;
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if (j == M) {
            cout << "Pattern found at index " << i << endl;
            patternFound = true;
        }
    }
    if (!patternFound)
        cout << "Pattern not found in the given text." << endl;

    return 0;
}
