// CNS Assignment No : Playfair Cipher
#include <bits/stdc++.h>

using namespace std;

class PlayFairCipher
{
private:

    static pair<vector<vector<char>>, unordered_map<char, pair<int, int>>>
    getKeyMatrixAndPositions(const string &key)
    {
        vector<vector<char>> keyMatrix(5, vector<char>(5));
        int i = 0, j = 0;
        unordered_set<char> set;
        unordered_map<char, pair<int, int>> position;

        for (char c : key)
        {
            // i and j are interchangebale according to playfair cipher
            if (c == 'j')
                c = 'i';

            // if current char is already present in the set then continue
            if (set.find(c) != set.end())
                continue;


            set.insert(c);
            keyMatrix[i][j] = c; // add it to the matrix
            position[c] = {i, j};

            j++;
            if (j == 5) // if we reach at the end of current row then shift to next row
            {
                j = 0;
                i++;
            }
        }
        
        // fill remaining characters which are are not in key in alphabetical order
        for (char c = 'a'; c <= 'z'; c++)
        {
            if (c == 'j')
                continue;

            if (set.find(c) != set.end())
                continue;

            set.insert(c);
            keyMatrix[i][j] = c;
            position[c] = {i, j};

            j++;
            if (j == 5)
            {
                j = 0;
                i++;
            }
        }

        position[j] = position[i];

        return {keyMatrix, position};
    }

    // get diagram or
    static vector<string> getDiagrams(const string &text)
    {
        int n = text.size();
        int i = 0;
        // vector of strings(size = 2) for plaintext
        vector<string> diagrams;

        while (i + 1 < n)
        {   
            // when adjacent characters are different
            if (text[i] != text[i + 1])
            {
                string d;
                d += tolower(text[i]);
                d += tolower(text[i + 1]);
                diagrams.push_back(d);

                i += 2;
            }
            else
            {
                string d;
                d += tolower(text[i]);
                d += 'x';
                diagrams.push_back(d);

                i++;
            }
        }

        // if last pair is incomplete add dummy character x
        if (i == n - 1)
        {
            string d;
            d += tolower(text[i]);
            d += 'x';
            diagrams.push_back(d);
        }

        return diagrams;
    }

public:
    static void printMatrix(vector<string> &mat){
        for(string str : mat)
            cout << str << " ";
        cout << endl;
    }

    static void printKeyMatrix(vector<vector<char>> &mat){
        for(int i=0; i<mat.size(); i++){
            for(int j=0; j< mat[0].size(); j++){
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
    }

    static string encode(const string &plaintext, const string &key)
    {
        //get key matrix using key
        auto [keyMatrix, position] = getKeyMatrixAndPositions(key);
        vector<string> diagrams = getDiagrams(plaintext);
        cout <<endl<< "Plain text diagrams: " << endl;

        printMatrix(diagrams);

        cout << endl << "Key Matrix: " << endl;

        printKeyMatrix(keyMatrix);

        string ciphertext;

        for (string &diagram : diagrams)
        {
            //cout << " Diagram " << diagram << "\n";
            auto [i0, j0] = position[diagram[0]];
            auto [i1, j1] = position[diagram[1]];

            //same row, diff col
            if (i0 == i1)
            {
                diagram[0] = keyMatrix[i0][(j0 + 1) % 5];
                diagram[1] = keyMatrix[i0][(j1 + 1) % 5];
            }
            //same col, diff row
            else if (j0 == j1)
            {
                diagram[0] = keyMatrix[(i0 + 1) % 5][j0];
                diagram[1] = keyMatrix[(i1 + 1) % 5][j0];
            }
            // diff row, diff col
            else
            {
                diagram[0] = keyMatrix[i0][j1];
                diagram[1] = keyMatrix[i1][j0];
            }

            ciphertext += diagram;
        }

        transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);
        return ciphertext;
    }

    static string decode(const string &ciphertext, const string &key)
    {
        auto [keyMatrix, position] = getKeyMatrixAndPositions(key);
        vector<string> diagrams = getDiagrams(ciphertext);
        string plaintext;

        for (string &diagram : diagrams)
        {
            auto [i0, j0] = position[diagram[0]];
            auto [i1, j1] = position[diagram[1]];

            if (i0 == i1)
            {
                diagram[0] = keyMatrix[i0][(j0 - 1 + 5) % 5];
                diagram[1] = keyMatrix[i0][(j1 - 1 + 5) % 5];
            }
            else if (j0 == j1)
            {
                diagram[0] = keyMatrix[(i0 - 1 + 5) % 5][j0];
                diagram[1] = keyMatrix[(i1 - 1 + 5) % 5][j0];
            }
            else
            {
                diagram[0] = keyMatrix[i0][j1];
                diagram[1] = keyMatrix[i1][j0];
            }

            plaintext += diagram;
        }

        return plaintext;
    }
};

int main()
{
    cout << "PlayFair Cipher:\n\n"
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
        plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace),
                        plaintext.end());

        cout << "Enter key (lowercase): ";
        string key;
        cin >> key;

        string ciphertext = PlayFairCipher::encode(plaintext, key);

        cout << "Plaintext:  " << plaintext << "\n"
             << "Ciphertext: " << ciphertext << "\n";
    }
    break;

    case 2:
    {
        cout << "Enter ciphertext (uppercase without spaces): ";
        string ciphertext;
        cin >> ciphertext;

        cout << "Enter key (lowercase): ";
        string key;
        cin >> key;

        string plaintext = PlayFairCipher::decode(ciphertext, key);

        cout << "Ciphertext: " << ciphertext << "\n"
             << "Plaintext:  " << plaintext << "\n";
    }
    break;

    default:
        cout << "Invalid choice!!\n";
        break;
    }

    return 0;
}