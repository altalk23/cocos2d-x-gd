#include "CCMouseDelegate.h"
#include "ccMacros.h"

CC_GD_ADD_BEGIN

NS_CC_BEGIN

//------------------------------------------------------------------
//
// CCKeyboardHandler
//
//------------------------------------------------------------------
CCMouseDelegate* CCMouseHandler::getDelegate()
{
    return m_pDelegate;
}

CCMouseHandler::~CCMouseHandler()
{
    if (m_pDelegate)
    {
        dynamic_cast<CCObject*>(m_pDelegate)->release();
    }  
}

void CCMouseHandler::setDelegate(CCMouseDelegate *pDelegate)
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

bool CCMouseHandler::initWithDelegate(CCMouseDelegate *pDelegate)
{
    CCAssert(pDelegate != NULL, "It's a wrong delegate!");

    m_pDelegate = pDelegate;
    dynamic_cast<CCObject*>(pDelegate)->retain();

    return true;
}

CCMouseHandler* CCMouseHandler::handlerWithDelegate(CCMouseDelegate *pDelegate)
{
    CCMouseHandler* pHandler = new CCMouseHandler;

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