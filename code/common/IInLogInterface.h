#ifndef __IInLogInterface_H__
#define __IInLogInterface_H__

#include <string>

typedef void(*FuncDebugLogCallback)(const std::string& strTmpLog, int iLevel);


extern FuncDebugLogCallback g_pDebugLogCallback;


#endif