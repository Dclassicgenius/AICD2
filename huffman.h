#pragma once
#include <iostream>
#include <string>
#include "Map.h"
#include "priority_queue.h"
#include "Queue.h"
using namespace std;
class HuffmanTree
{
private:
	class Node
	{
	public:
		char symbol;
		int val;
		Node* right;
		Node* left;

		Node(char symbol, int val, Node* left, Node* right)
		{
			this->symbol = symbol;
			this->val = val;
			this->right = right;
			this->left = left;
		}

		~Node()
		{
			this->right = nullptr;
			this->left = nullptr;
		}
	};

	Node* root;
	priority_queue<Node*> nodes_list; 

	void clear(Node* node)
	{
		if (node != nullptr)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	//creates code and decode tables 
	void Fill(Map<char, string>& code_table, Map<string, char>& decode_table, Node* direction, string& code_str)
	{
		if (direction != nullptr)
		{
			//if node is leaf
			if (direction->left == nullptr && direction->right == nullptr)
			{
				code_table.insert(direction->symbol, code_str);
				decode_table.insert(code_str, direction->symbol);
			}
			code_str.push_back('0');
			Fill(code_table, decode_table, direction->left, code_str);

			code_str.push_back('1');
			Fill(code_table, decode_table, direction->right, code_str);
		}

		if (!code_str.empty())
			code_str.pop_back();
	}

public:

	Map<char, string> code_table;
	Map<string, char> decode_table;

	HuffmanTree()
	{
		root = nullptr;
	}

	~HuffmanTree()
	{
		clear(root);
		root = nullptr;
	}

	//create Huffman tree from map
	void create(Map<char, int>& arr)
	{
		if (arr.getSize() == 0)
			throw logic_error("empty map");

		List<char> symbols;
		arr.get_keys(symbols);

		//filling priority queue with nodes
		while (!symbols.isEmpty())
		{
			Node* node = new Node(symbols.at(0), arr.find(symbols.at(0)), nullptr, nullptr);
			symbols.pop_front();
			nodes_list.insert(node, node->val);
		}

		//connects nodes
		while (nodes_list.getSize() > 1)
		{
			Node* left = nodes_list.extract_min();
			Node* right = nodes_list.extract_min();

			Node* parent = new Node(0, left->val + right->val, left, right);

			nodes_list.insert(parent, parent->val);
		}

		root = nodes_list.extract_min();

		string code_str;
		Fill(code_table, decode_table, root, code_str); 

	}
};

//get Huffman code for the string
inline string Encode(const string& enc, HuffmanTree& encod)
{
	Map<char, int> frequency;

	//counts the occurrence of symbols
	for (auto symbol : enc)
	{
		if (frequency.contains(symbol))
			frequency.update(symbol, frequency.find(symbol) + 1);
		else
			frequency.insert(symbol, 1);
	}

	encod.create(frequency); 

	//encoding string 
	string encode;
	for (auto symbol : enc)
	{
		encode += encod.code_table.find(symbol);
		encode += " ";
	}
	encode.pop_back();

	return encode;
}

//decodes the string
inline string Decode(const string& encoded_str, HuffmanTree& h_tree)
{
	if (h_tree.decode_table.getSize() == 0)
		throw logic_error("empty table to decode");

	//filling queue with the codes
	Queue<string> codes;
	string code;
	for (auto symbol : encoded_str)
	{
		if (symbol == '1' || symbol == '0')
			code += symbol;
		else if (symbol == ' ')
		{
			codes.enqueue(code);
			code.clear();
		}
		else
			throw invalid_argument("invalid code");
	}

	codes.enqueue(code);
	code.clear();

	//decodes code string with decode table created from Huffman's tree
	string decode;
	while (codes.getSize() > 0)
	{
		code = codes.dequeue();

		if (!h_tree.decode_table.contains(code))
			throw invalid_argument("wrong attached huff. tree");

		decode += h_tree.decode_table.find(code);
	}

	return decode;
}

//deletes all spaces in the string
inline string trim(string str)
{
	string trimmed;
	for (auto element : str)
	{
		if (element != ' ')
			trimmed += element;
	}

	return trimmed;
}

//calculating Compression Coefficient 
inline float CompCoeff(string& original, string& coded)
{
	if (trim(coded).empty())
		throw logic_error("Coded string cannot be empty");

	return (float)(original.length() * 8) / trim(coded).length();
}

inline void Print(HuffmanTree& h_tree, const string& encod)
{
	Map<char, int> frequency;
	string symbols;

	//calculates symbols occurrence
	for (auto symbol : encod)
	{
		if (frequency.contains(symbol))
			frequency.update(symbol, frequency.find(symbol) + 1);
		else
		{
			symbols += symbol;
			frequency.insert(symbol, 1);
		}
	}

	for (auto element : symbols)
	{
		cout << "symbol: " << element << "\tcode: " << h_tree.code_table.find(element) << "\tfrequency: " << frequency.find(element) << endl;
	}
}
