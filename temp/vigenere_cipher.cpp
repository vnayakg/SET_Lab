//CNS Assingment No : Vigenere Cipher
//PRN: 2019BTECS00032
#include <bits/stdc++.h>

using namespace std;

string vigenerDecrypt(string cipher, string key)
{
    string decodedText;

    int keyLen = key.size();
    int cipherLen = cipher.size();

    int keyInd = 0;

    for (int i = 0; i < cipherLen; i++)
    {
        char k = key[keyInd % keyLen] - 'a';
        char c = cipher[i] - 'A';

        char ch = 'a' + (c - k + 26) % 26;

        keyInd++;

        decodedText.push_back(ch);
    }

    return decodedText;
}

string vigenerEncrypt(string plainText, string key)
{
    string cipher;

    int keyLen = key.size();
    int ptLen = plainText.size();

    int keyInd = 0;

    for (int i = 0; i < ptLen; i++)
    {
        char k = key[keyInd % keyLen] - 'a';
        char c = plainText[i] - 'a';
        
        char ch = 'A' + (c + k) % 26;

        cipher.push_back(ch);
        keyInd++;
    }

    return cipher;
}

int main()
{
    cout << "Caeser Cipher:\n\n"
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
        getline(cin, plaintext);
        getline(cin, plaintext);

        string temp;
        for (int i = 0; i < plaintext.size(); i++)
        {
            if (plaintext[i] != ' ')
                temp.push_back(plaintext[i]);
        }
        plaintext = temp;

        cout << "Enter key (lowercase): ";
        string key;
        cin >> key;

        string ciphertext = vigenerEncrypt(plaintext, key);

        cout << "Plaintext:  " << plaintext << "\n"
             << "Ciphertext: " << ciphertext << "\n";
    }
    break;

    case 2:
    {
        cout << "Enter ciphertext (Uppercase): ";
        string ciphertext;
        cin >> ciphertext;

        cout << "Enter key (lowercase): ";
        string key;
        cin >> key;

        string plaintext = vigenerDecrypt(ciphertext, key);

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