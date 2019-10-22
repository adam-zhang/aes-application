#include "AESWrapper.h"
#include <openssl/aes.h>
#include <iostream>
#include "base64.h"

using namespace std;

AESWrapper::AESWrapper()
{
}

AESWrapper::~AESWrapper()
{
}

#define BLOCK_SIZE 16

static vector<unsigned char> encrypt(const vector<unsigned char>& key, const vector<unsigned char>& data)
{
	vector<unsigned char> out(data.size());
	AES_KEY aesKey = {0};
	AES_set_encrypt_key(key.data(), key.size() * 8, &aesKey);
	for(size_t i = 0; i < out.size() ; i += BLOCK_SIZE)
		AES_encrypt(data.data() + i, out.data() + i, &aesKey); // AES_ENCRYPT);
	return out;
}


static vector<unsigned char> decrypt(const vector<unsigned char>& key, const vector<unsigned char>& data)
{
	AES_KEY aesKey = {0};
	AES_set_decrypt_key(key.data(), key.size() * 8, &aesKey);
	vector<unsigned char> out(data.size());
	for(size_t i = 0; i < data.size(); i += BLOCK_SIZE)
		AES_decrypt(data.data() + i, out.data() + i, &aesKey);
	return out;
}


static vector<unsigned char> to_vector(const string& s)
{
	return vector<unsigned char>(s.begin(), s.end());
}

string AESWrapper::encrypt(const std::string& key, const vector<unsigned char>& data)
{
	auto v = ::encrypt(to_vector(key), data);
	return base64_encode(v);
}

vector<unsigned char> AESWrapper::decrypt(const string& key, const string& data )
{
	auto v = base64_decode(data);
	return ::decrypt(to_vector(key), v);
}
