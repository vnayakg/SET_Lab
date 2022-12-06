// CNS Assignment No : Cryptanalysis

let dict = require("./dict");

let cipherText = "go*kbo*sxnskx*";
let key;

// function to decrypt the word
const wordDecrypt = (wordPart) => {
  let plainText;

  for (key = 9; key < 11; key++) {
    plainText = "";
    for (ch in wordPart) {
      let tmp =
        wordPart[ch].charCodeAt(0) - key < 97
          ? wordPart[ch].charCodeAt(0) - key + 26
          : wordPart[ch].charCodeAt(0) - key;

      plainText += String.fromCharCode(tmp);
    }
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

console.log("Deciphered Text: ", plainText.toUpperCase());
