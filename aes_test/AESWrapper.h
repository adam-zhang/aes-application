#ifndef __AESWRAPPER__H
#define __AESWRAPPER__H

#include <string>
#include <vector>

class AESWrapper
{
private:
	AESWrapper();
	~AESWrapper();
public:
	static std::string encrypt(const std::string& key, const std::vector<unsigned char>& data);
	static std::vector<unsigned char> decrypt(const std::string& key, const std::string& data);
};
#endif//__AESWRAPPER__H
