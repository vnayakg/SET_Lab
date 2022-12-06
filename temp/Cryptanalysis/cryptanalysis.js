// importing common words dictionary
let dict = require("./dict").map(str => str.toLowerCase());

//input of cipher text using file
let cipherText = require("./cipherText").toLowerCase();
//console.log(cipherText)
let key;

// function to decrypt the word
const wordDecrypt = (wordPart) => {
  let plainText;
  //taking various keys
  for (key = 1; key < 26; key++) {
    plainText = "";

    for (ch in wordPart) {
      let tmp =
        (wordPart[ch].charCodeAt(0) - key) < 97
          ? wordPart[ch].charCodeAt(0) - key + 26
          : wordPart[ch].charCodeAt(0) - key;

      plainText += String.fromCharCode(tmp);
    }
	//console.log("inside decrypt: ", plainText)


    for (word in dict) {
      if (dict[word] === plainText) {
        console.log(
          "Word " +
            `${dict[word].toUpperCase()}` +
            " found at location: " +
            word +
            "!"
        );
        return dict[word];
      }
    }
  }
};

let plainText = "";
let wordPart = "";

// analysing ciphertext

for (num in cipherText) {
  if (cipherText[num] === "*" || Number(num) === Number(cipherText.length)) {
    plainText += wordDecrypt(wordPart) + " ";
    wordPart = "";
  }
  if (cipherText[num] !== "*") {
    wordPart += cipherText[num];
  }
}

console.log("Deciphered Text: ", plainText.toLowerCase());
