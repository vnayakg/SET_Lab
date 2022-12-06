// CNS Assignment No : Columnar Cipher
// PRN: 2019BTECS00032

#include <bits/stdc++.h>

using namespace std;

class ColumnarCipher
{
private:
    static void printMatrix(vector<string> &mat){
        
        for(string str : mat)
            
            cout << str << endl;
        cout << endl;
    }
    // sort the given key and their index to find the order in which we have to read
    static vector<int> colSequence(const vector<int> &key)
    {
        vector<pair<int, int>> v;
        int n = key.size();

        for (int i = 0; i < n; i++)
            v.push_back({key[i], i});

        // sort on first index ie given sequence so that we get the order
        sort(v.begin(), v.end());

        vector<int> seq;
        for (pair<int, int> p : v)
            seq.push_back(p.second);

        return seq;
    }

public:
    // encrypt plain text
    static string encrypt(const string &plaintext, const vector<int> &key)
    {
        int n = key.size();
        int m = ceil((float)plaintext.size() / n);

        // matrix with initial character as X, so trailing X are dummy characters
        vector<string> mat(m, string(n, 'X'));

        int i = 0, j = 0;

        // add plain text to matrix and capitalised every character
        for (char c : plaintext)
        {
            mat[i][j] = toupper(c);

            j++;
            if (j == n)
            {
                i++;
                j = 0;
            }
        }
        cout<< endl << "Matrix: " << endl;
        printMatrix(mat);
        string ciphertext;
        // read according to the sequence that we generated using col sequence and add it to the cipher text
        for (int j : colSequence(key))
        {
            for (int i = 0; i < m; i++)
                ciphertext += mat[i][j];
        }

        return ciphertext;
    }

    // decryption
    static string decrypt(const string &ciphertext, const vector<int> &key)
    {
        int n = key.size();
        int m = ceil((float)ciphertext.size() / n);

        // initialised matrix with the dummy character
        vector<string> mat(m, string(n, '_'));

        int k = 0;
        // again using the same key sequence to add characters to the matrix
        for (int j : colSequence(key))
        {
            for (int i = 0; i < m; i++)
                mat[i][j] = tolower(ciphertext[k++]);
        }

        string plaintext;
        // to get the plain text read the matrix row by row
        for (string &row : mat)
            plaintext += row;

        return plaintext;
    }
};

// convert inserted key by user to vector using string stream
vector<int> getKey(const string &tempKey)
{
    stringstream ss(tempKey);
    vector<int> key;
    int k;

    while (ss >> k)
        key.push_back(k);

    return key;
}

// Main function
int main()
{
    cout << "Columnar Cipher:\n\n"
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

        cout << "Enter key (space separated integers 1 to numOfCols in random "
                "order): ";
        string tempKey;
        getline(cin, tempKey);
        vector<int> key = getKey(tempKey);

        string ciphertext = ColumnarCipher::encrypt(plaintext, key);

        cout << "Plaintext:  " << plaintext << "\n"
             << "Ciphertext: " << ciphertext << "\n";
    }
    break;

    case 2:
    {
        cout << "Enter ciphertext (uppercase without spaces): ";
        string ciphertext;
        cin >> ciphertext;

        cout << "Enter key (space separated integers 1 to num of cols in random "
                "order): ";
        string tempKey;
        getline(cin, tempKey);
        getline(cin, tempKey);
        vector<int> key = getKey(tempKey);

        string plaintext = ColumnarCipher::decrypt(ciphertext, key);

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