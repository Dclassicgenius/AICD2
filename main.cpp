#include "huffman.h"

using namespace std;

int main()
{
	string str;
	cout << "Enter the string to encode: ";
	getline(cin, str);

	HuffmanTree encoding;
	auto code = Encode(str, encoding);
	auto decode = Decode(code, encoding);

	cout << "\nMemory used: " << str.length() * 8 << " bits" << endl;

	cout << "\nCodes and frequency table:" << endl;
	Print(encoding, str);

	cout << "\nEncoding result: " << code << endl;
	cout << "Memory used: " << trim(code).length() << " bits" << endl;
	cout << "\nDecoding result: " << decode << endl;
	cout << "\nCompression coefficient: " << CompCoeff(str, code) << endl;
	return 0;
}