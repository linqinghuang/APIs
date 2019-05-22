#ifndef __DESCrypto_H__
#define __DESCrypto_H__

#include <string>
#include <vector>

class CDesCrypto
{
public:
	std::string EncryptString(const std::string& strInput);
	std::string DecryptString(const std::string& strInput);

public:
	CDesCrypto(const std::vector<unsigned char>& vecInit, const std::vector<unsigned char>& vecKey);
	~CDesCrypto();

private:
	CDesCrypto();
	CDesCrypto(const CDesCrypto& other);
	CDesCrypto& operator=(const CDesCrypto& other);

private:
	std::vector<unsigned char> m_vecInit;
	std::vector<unsigned char> m_vecKey;
};

#endif