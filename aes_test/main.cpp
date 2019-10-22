#include <openssl/aes.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cassert>

#include "base64.h"

using namespace std;

static const size_t BLOCK_SIZE = 16;


string to_hex(const vector<unsigned char>& data)
{
	stringstream ss;
	for(auto c : data)
		ss << hex << setw(2) << setfill('0') << unsigned int(unsigned char(c)) << " ";
	//cout << ss.str() << endl;
	return ss.str();
}

vector<unsigned char> pad(const vector<unsigned char>& data)
{
	auto out = data;
	auto mod = data.size() % BLOCK_SIZE;
	if (mod != 0)
	{
		for(size_t i = 0; i != BLOCK_SIZE - mod; ++i )
			out.push_back(0);
	}
	assert(out.size() % BLOCK_SIZE == 0);
	return out;
}


vector<unsigned char> encrypt(const vector<unsigned char>& key, const vector<unsigned char>& data)
{
	vector<unsigned char> out(data.size());
	AES_KEY aesKey = {0};
	AES_set_encrypt_key(key.data(), key.size() * 8, &aesKey);
	for(size_t i = 0; i < out.size() ; i += BLOCK_SIZE)
		AES_encrypt(data.data() + i, out.data() + i, &aesKey); // AES_ENCRYPT);
	return out;
}


vector<unsigned char> decrypt(const vector<unsigned char>& key, const vector<unsigned char>& data)
{
	AES_KEY aesKey = {0};
	AES_set_decrypt_key(key.data(), key.size() * 8, &aesKey);
	vector<unsigned char> out(data.size());
	for(size_t i = 0; i < data.size(); i += BLOCK_SIZE)
		AES_decrypt(data.data() + i, out.data() + i, &aesKey);
	return out;
}

vector<unsigned char> to_vector(const string& s)
{
	return vector<unsigned char>(s.begin(), s.end());
}


string key()
{
	return "0123456789abcdef";
}

string aes_encrypt(const vector<unsigned char>& data)
{
	auto v = encrypt(to_vector(key()), data);
	to_hex(v);
	return base64_encode(v);
}

vector<unsigned char> aes_decrypt(const string& data)
{
	auto v = base64_decode(data);
	return decrypt(to_vector(key()), v);
}


string content()
{
	return "Hello";
}


int main()
{
	
	auto data = pad(to_vector(content()));
	auto s1 = aes_encrypt(data);
	cout << "s1:" << s1 << endl;
	auto s = aes_decrypt(s1);
	cout << "s:" << (s.data()) << endl;
	//s = "DWUdW+b50jgAz0/3LF3V9w==";
	//aes_decrypt( s);
	//cout << v.data() << endl;
	//string s = "d6b74989e9cbf7910fe77b7e051c742e";
	//cout << s.size() << endl;
	return 0;
}
