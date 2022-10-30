#ifndef __CCMOUSE_DISPATCHER_H__
#define __CCMOUSE_DISPATCHER_H__

#include "CCMouseDelegate.h"
#include "../../cocoa/CCArray.h"

CC_GD_ADD_BEGIN

NS_CC_BEGIN

class CC_DLL CCMouseDispatcher : public CCObject 
{
public:
	CCMouseDispatcher();
	virtual ~CCMouseDispatcher();

	void addDelegate(CCMouseDelegate* pDelegate);

	void removeDelegate(CCMouseDelegate* pDelegate);

	void forceAddDelegate(CCMouseDelegate* pDelegate);

	void forceRemoveDelegate(CCMouseDelegate* pDelegate);

	bool dispatchScrollMSG(float x, float y);

protected:
	CCArray* m_pDelegates;
	bool m_bLocked;
	bool m_bToAdd;
	bool m_bToRemove;
	ccCArray* m_pHandlersToAdd;
	ccCArray* m_pHandlersToRemove;
};

NS_CC_END

CC_GD_ADD_END

#endif
