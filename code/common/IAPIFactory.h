/**
@Copyright Copyright (C), 2017, Hytera
@file		DvrsTimer.h
@created	2017/02/16
@brief

@author	xujinghua
*/

#ifndef __IAPIFactory_H__
#define __IAPIFactory_H__

#include "IAPIObject.h"

namespace MRPS
{

	class IAPIFactory
	{
	public:
		virtual IAPIObject* CreateAPIObject() = 0;
		virtual void DestroyAPIObject(IAPIObject* pAPIObject) = 0;
		virtual APIType GetFactoryType() = 0;

	public:
		virtual ~IAPIFactory(){}

	protected:
		IAPIFactory(){}
	};
};



#endif