#include "pch.h"
#include "CppUnitTest.h"
#include "../huffm/huffman.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace huffmantest
{
	TEST_CLASS(huffmantest)
	{
	public:
		Assert assert;
		TEST_METHOD(create_empty)
		{
			HuffmanTree enc;
			Map<char, int> name;

			try
			{
				enc.create(name);
			}
			catch (logic_error& error)
			{
				assert.AreEqual("empty map", error.what());
			}
		}

		TEST_METHOD(encode)
		{
			HuffmanTree h_tree;
			string str = "mississippi river";
			string result = "1011 11 00 00 11 00 00 11 010 010 11 1000 011 11 1001 1010 011";

			assert.AreEqual(result, Encode(str, h_tree));
		}

		TEST_METHOD(decode)
		{
			HuffmanTree h_tree;
			string str = "what a day!";
			string code = Encode(str, h_tree);

			assert.AreEqual(str, Decode(code, h_tree));
		}

		TEST_METHOD(decode_empty)
		{
			HuffmanTree h_tree;
			string code = "10 100 111";

			try
			{
				string decode = Decode(code, h_tree);
			}
			catch (logic_error& error)
			{
				assert.AreEqual("empty table to decode", error.what());
			}
		}

		TEST_METHOD(trim_)
		{
			string str = "ha p p y days";
			string result = "happydays";
			assert.AreEqual(result, trim(str));
		}

		TEST_METHOD(compCoeff_empty)
		{
			string str = "rainy days";
			string code;

			try
			{
				float a = CompCoeff(str, code);
			}
			catch (logic_error& error)
			{
				assert.AreEqual("Coded string cannot be empty", error.what());
			}
		}
	};
}



