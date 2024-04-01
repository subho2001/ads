#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int NO_OF_CHARS = 256;

void printBadCharTable(int badchar[]) {
    cout << "Bad Character Table:" << endl;
    for (int i = 0; i < NO_OF_CHARS; i++) {
        if (badchar[i] != -1) {
            cout << "Character '" << char(i) << "': Shift=" << badchar[i] << endl;
        }
    }
    cout << endl;
}

void badCharHeuristic(string pattern, int size, int badchar[]) {
    memset(badchar, -1, sizeof(int) * NO_OF_CHARS);
    for (int i = 0; i < size; i++) {
        badchar[(int)pattern[i]] = i;
    }
}

void search(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pattern, m, badchar);

    printBadCharTable(badchar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << endl;
            s += (s + m < n) ? m - badchar[text[s + m]] : 1;
        } else {
            int badCharShift = j - badchar[text[s + j]];
            if (badCharShift < 1)
                badCharShift = 1;
            s += badCharShift;
        }
    }
}

int main() {
    string text = "ABAAABCDABCDABC";
    string pattern = "ABCDABC";

    search(text, pattern);

    return 0;
}
