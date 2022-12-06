// CNS Assignment No : Railfence Cipher
// PRN: 2019BTECS00032

#include <bits/stdc++.h>

using namespace std;

class RailFenceCipher
{
public:
    static string encrypt(string plaintext, int depth)
    {
        // making all chanracters uppercase
        transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);

        vector<char> levels[depth];

        int curLevel = 0;
        int turn = 1; // to change the level

        for (int i = 0; i < plaintext.length(); i++)
        {
            levels[curLevel].push_back(plaintext[i]);

            //if we reach at end then start filling 
            if (curLevel == depth - 1 && turn == 1)
            {
                turn = -1;
            }
            else if (curLevel == 0 && turn == -1)
            {
                turn = 1;
            }
            curLevel += turn;
        }
        string ciphertext;
        // iterate over all level and append  to form cipher text
        for (int i = 0; i < depth; i++)
        {
            for (char c : levels[i])
                ciphertext += c;
        }
        return ciphertext;
    }

    // decrypt
    static string decrypt(string ciphertext, int depth)
    {
        int curLevel = 0;
        int turn = 1;
        vector<int> counts(depth, 0);

        // count total no of characters in each level
        for (int i = 0; i < ciphertext.length(); i++)
        {
            counts[curLevel]++;
            if (curLevel == depth - 1 && turn == 1)
            {
                turn = -1;
            }
            else if (curLevel == 0 && turn == -1)
            {
                turn = 1;
            }
            curLevel += turn;
        }
        // to get all characters at each level
        vector<string> letters(depth);

        int start_index = 0;

        for (int i = 0; i < depth; i++)
        {
            int c = counts[i];
            letters[i] = ciphertext.substr(start_index, c);
            start_index += c;
        }

        string plaintext;

        fill(counts.begin(), counts.end(), 0);

        curLevel = 0;
        turn = 1;
        // add first charcter of each level to form the plain text
        for (int i = 0; i < ciphertext.length(); i++)
        {
            plaintext += letters[curLevel][counts[curLevel]];
            counts[curLevel]++;

            if (curLevel == depth - 1 && turn == 1)
            {
                turn = -1;
            }
            else if (curLevel == 0 && turn == -1)
            {
                turn = 1;
            }
            curLevel += turn;
        }

        return plaintext;
    }
};

int main()
{
    cout << "Railfence Cipher:\n\n"
         << "Enter your choice:\n"
         << "1. Encrypt\n"
         << "2. Decrypt\n"
         << "> ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "Enter plaintext (lowercase): ";
        string plaintext;
        getline(cin, plaintext); // buffer reset
        getline(cin, plaintext);
        plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace),plaintext.end());

        cout << "Enter depth (int): ";
        int depth;
        cin >> depth;

        string ciphertext = RailFenceCipher::encrypt(plaintext, depth);

        cout << "Plaintext:  " << plaintext << "\n"
             << "Ciphertext: " << ciphertext << "\n";
    }
    break;

    case 2:
    {
        cout << "Enter ciphertext (uppercase without spaces): ";
        string ciphertext;
        cin >> ciphertext;

        cout << "Enter key (lowercase: ";
        int depth;
        cin >> depth;

        string plaintext = RailFenceCipher::decrypt(ciphertext, depth);

        cout << "Ciphertext: " << ciphertext << "\n" << "Plaintext:  " << plaintext << "\n";
    }
    break;

    default:
        cout << "Invalid choice!!\n";
        break;
    }
}