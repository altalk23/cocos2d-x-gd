#include "CCKeyboardDispatcher.h"
#include "support/data_support/ccCArray.h"

CC_GD_ADD_BEGIN

NS_CC_BEGIN

//------------------------------------------------------------------
//
// CCKeyboardDispatcher
//
//------------------------------------------------------------------
CCKeyboardDispatcher::CCKeyboardDispatcher()
: m_bLocked(false)
, m_bToAdd(false)
, m_bToRemove(false)
, m_bShiftPressed(false)
, m_bControlPressed(false)
, m_bAltPressed(false)
, m_bCommandPressed(false)
{
    m_pDelegates = CCArray::create();
    m_pDelegates->retain();

    m_pHandlersToAdd    = ccCArrayNew(8);
    m_pHandlersToRemove = ccCArrayNew(8);
}

CCKeyboardDispatcher::~CCKeyboardDispatcher()
{
    CC_SAFE_RELEASE(m_pDelegates);
    if (m_pHandlersToAdd)
    {
        ccCArrayFree(m_pHandlersToAdd);
    }
    
    if (m_pHandlersToRemove)
    {
        ccCArrayFree(m_pHandlersToRemove);
    }    
}

void CCKeyboardDispatcher::removeDelegate(CCKeyboardDelegate* pDelegate)
{
    if (!pDelegate)
    {
        return;
    }
    if (! m_bLocked)
    {
        forceRemoveDelegate(pDelegate);
    }
    else
    {
        ccCArrayAppendValue(m_pHandlersToRemove, pDelegate);
        m_bToRemove = true;
    }
}

void CCKeyboardDispatcher::addDelegate(CCKeyboardDelegate* pDelegate)
{
    if (!pDelegate)
    {
        return;
    }

    if (! m_bLocked)
    {
        forceAddDelegate(pDelegate);
    }
    else
    {
        ccCArrayAppendValue(m_pHandlersToAdd, pDelegate);
        m_bToAdd = true;
    }
}

void CCKeyboardDispatcher::forceAddDelegate(CCKeyboardDelegate* pDelegate)
{
    CCKeyboardHandler* pHandler = CCKeyboardHandler::handlerWithDelegate(pDelegate);

    if (pHandler)
    {
        m_pDelegates->addObject(pHandler);
    }
}

void CCKeyboardDispatcher::forceRemoveDelegate(CCKeyboardDelegate* pDelegate)
{
    CCKeyboardHandler* pHandler = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pDelegates, pObj)
    {
        pHandler = (CCKeyboardHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            m_pDelegates->removeObject(pHandler);
            break;
        }
    }
}

enumKeyCodes CCKeyboardDispatcher::convertKeyCode(enumKeyCodes key) {
    switch (key) {
        case KEY_ArrowUp:
            return KEY_Up;
        case KEY_ArrowDown:
            return KEY_Down;
        case KEY_ArrowLeft:
            return KEY_Left;
        case KEY_ArrowRight:
            return KEY_Right;
        default:
            return key;
    }
}

bool CCKeyboardDispatcher::dispatchKeyboardMSG(enumKeyCodes key, bool release)
{
    CCKeyboardHandler*  pHandler = NULL;
    CCKeyboardDelegate* pDelegate = NULL;

    m_bLocked = true;

    if (m_pDelegates->count() > 0)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pDelegates, pObj)
        {
            CC_BREAK_IF(!pObj);

            pHandler = (CCKeyboardHandler*)pObj;
            pDelegate = pHandler->getDelegate();

            if (release) {
                pDelegate->keyUp(key);
            }
            else {
                pDelegate->keyDown(key);
            }
        }
    }

    m_bLocked = false;
    if (m_bToRemove)
    {
        m_bToRemove = false;
        for (unsigned int i = 0; i < m_pHandlersToRemove->num; ++i)
        {
            forceRemoveDelegate((CCKeyboardDelegate*)m_pHandlersToRemove->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersToRemove);
    }

    if (m_bToAdd)
    {
        m_bToAdd = false;
        for (unsigned int i = 0; i < m_pHandlersToAdd->num; ++i)
        {
            forceAddDelegate((CCKeyboardDelegate*)m_pHandlersToAdd->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersToAdd);
    }

    return true;
}

NS_CC_END

CC_GD_ADD_END
