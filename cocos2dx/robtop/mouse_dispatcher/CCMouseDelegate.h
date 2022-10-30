#ifndef __CCMOUSE_DELEGATE_H__
#define __CCMOUSE_DELEGATE_H__

#include "../../include/ccMacros.h"
#include "../../cocoa/CCObject.h"

CC_GD_ADD_BEGIN

NS_CC_BEGIN

class CC_DLL CCMouseDelegate 
{
public:
	virtual void rightKeyDown() {}

	virtual void rightKeyUp() {}

	virtual void scrollWheel(float x, float y) {}
};

class CC_DLL CCMouseHandler : public CCObject
{
public:
	
	virtual ~CCMouseHandler();

	CCMouseDelegate* getDelegate();

	static CCMouseHandler* handlerWithDelegate(CCMouseDelegate* pDelegate);

	virtual bool initWithDelegate(CCMouseDelegate* pDelegate);

	void setDelegate(CCMouseDelegate* pDelegate);

protected:
	CCMouseDelegate* m_pDelegate;
};

NS_CC_END

CC_GD_ADD_END

#endif
