#include "CCKeyboardDelegate.h"
#include "ccMacros.h"

CC_GD_ADD_BEGIN

NS_CC_BEGIN

//------------------------------------------------------------------
//
// CCKeyboardHandler
//
//------------------------------------------------------------------
CCKeyboardDelegate* CCKeyboardHandler::getDelegate()
{
    return m_pDelegate;
}

CCKeyboardHandler::~CCKeyboardHandler()
{
    if (m_pDelegate)
    {
        dynamic_cast<CCObject*>(m_pDelegate)->release();
    }  
}

void CCKeyboardHandler::setDelegate(CCKeyboardDelegate *pDelegate)
{
    if (pDelegate)
    {
        dynamic_cast<CCObject*>(pDelegate)->retain();
    }

    if (m_pDelegate)
    {
        dynamic_cast<CCObject*>(m_pDelegate)->release();
    }
    m_pDelegate = pDelegate;
}

bool CCKeyboardHandler::initWithDelegate(CCKeyboardDelegate *pDelegate)
{
    CCAssert(pDelegate != NULL, "It's a wrong delegate!");

    m_pDelegate = pDelegate;
    dynamic_cast<CCObject*>(pDelegate)->retain();

    return true;
}

CCKeyboardHandler* CCKeyboardHandler::handlerWithDelegate(CCKeyboardDelegate *pDelegate)
{
    CCKeyboardHandler* pHandler = new CCKeyboardHandler;

    if (pHandler)
    {
        if (pHandler->initWithDelegate(pDelegate))
        {
            pHandler->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pHandler);
        }
    }

    return pHandler;
}

NS_CC_END

CC_GD_ADD_END