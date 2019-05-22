#include "DESCrypto.h"
#include "APICommonLog.h"
#include "APICommonDef.h"
#include "Poco/Format.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CipherKey.h"
#include "Poco/Crypto/CipherFactory.h"
#include "Poco/Exception.h"


/************************************************************************/
/*                                                                      */
/************************************************************************/
std::string CDesCrypto::EncryptString(const std::string& strInput)
{
	try
	{
		Poco::Crypto::CipherKey key("des-cbc");
		key.setIV(m_vecInit);
		key.setKey(m_vecKey);
		Poco::Crypto::Cipher::Ptr pCipher = Poco::Crypto::CipherFactory::defaultFactory().createCipher(key);
		return pCipher->encryptString(strInput, Poco::Crypto::Cipher::ENC_BASE64);
	}	
	catch (Poco::Exception& ex)
	{
		std::string strTmpLog = Poco::format("CDesCrypto::EncryptString failed! errMsg = %s", std::string(ex.displayText()));
		WRITE_ERROR_LOG(strTmpLog);
		return "";
	}	
}

std::string CDesCrypto::DecryptString(const std::string& strInput)
{
	try
	{
		Poco::Crypto::CipherKey key("des-cbc");
		key.setIV(m_vecInit);
		key.setKey(m_vecKey);
		Poco::Crypto::Cipher::Ptr pCipher = Poco::Crypto::CipherFactory::defaultFactory().createCipher(key);
		return pCipher->decryptString(strInput, Poco::Crypto::Cipher::ENC_BASE64);
	}
	catch (Poco::Exception& ex)
	{
		std::string strTmpLog = Poco::format("CDesCrypto::DecryptString failed! errMsg = %s", std::string(ex.displayText()));
		WRITE_ERROR_LOG(strTmpLog);
		return "";
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CDesCrypto::CDesCrypto(const std::vector<unsigned char>& vecInit, const std::vector<unsigned char>& vecKey)
: m_vecInit(m_vecInit), m_vecKey(vecKey)
{

}

CDesCrypto::~CDesCrypto()
{

}