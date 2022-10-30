#ifndef __CCKEYBOARD_DISPATCHER_H__
#define __CCKEYBOARD_DISPATCHER_H__

#include "CCKeyboardDelegate.h"
#include "../../cocoa/CCArray.h"

CC_GD_ADD_BEGIN

NS_CC_BEGIN

class CC_DLL CCKeyboardDispatcher : public CCObject 
{
public:
	CCKeyboardDispatcher();
	virtual ~CCKeyboardDispatcher();

	void addDelegate(CCKeyboardDelegate* pDelegate);
	void removeDelegate(CCKeyboardDelegate* pDelegate);

	void forceAddDelegate(CCKeyboardDelegate* pDelegate);
	void forceRemoveDelegate(CCKeyboardDelegate* pDelegate);

	enumKeyCodes convertKeyCode(enumKeyCodes key);

	bool dispatchKeyboardMSG(enumKeyCodes key, bool release);
	
	inline bool getAltKeyPressed() const {
		return m_bAltPressed;
	}
	inline bool getCommandKeyPressed() const {
		return m_bCommandPressed;
	}
	inline bool getControlKeyPressed() const {
		return m_bControlPressed;
	}
	inline bool getShiftKeyPressed() const {
		return m_bShiftPressed;
	}

	const char* keyToString(enumKeyCodes key);

	void updateModifierKeys(bool shft, bool ctrl, bool alt, bool cmd);

protected:
	CCArray* m_pDelegates;
	bool m_bLocked;
	bool m_bToAdd;
	bool m_bToRemove;
	ccCArray* m_pHandlersToAdd;
	ccCArray* m_pHandlersToRemove;
	bool m_bShiftPressed;
	bool m_bControlPressed;
	bool m_bAltPressed;
	bool m_bCommandPressed;
	//there's more here, check the initializer
};

NS_CC_END

CC_GD_ADD_END

#endif
