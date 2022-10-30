#include "CCMouseDispatcher.h"
#include "support/data_support/ccCArray.h"

CC_GD_ADD_BEGIN

NS_CC_BEGIN

//------------------------------------------------------------------
//
// CCMouseDispatcher
//
//------------------------------------------------------------------
CCMouseDispatcher::CCMouseDispatcher()
: m_bLocked(false)
, m_bToAdd(false)
, m_bToRemove(false)
{
    m_pDelegates = CCArray::create();
    m_pDelegates->retain();

    m_pHandlersToAdd    = ccCArrayNew(8);
    m_pHandlersToRemove = ccCArrayNew(8);
}

CCMouseDispatcher::~CCMouseDispatcher()
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

void CCMouseDispatcher::removeDelegate(CCMouseDelegate* pDelegate)
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

void CCMouseDispatcher::addDelegate(CCMouseDelegate* pDelegate)
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

void CCMouseDispatcher::forceAddDelegate(CCMouseDelegate* pDelegate)
{
    CCMouseHandler* pHandler = CCMouseHandler::handlerWithDelegate(pDelegate);

    if (pHandler)
    {
        m_pDelegates->addObject(pHandler);
    }
}

void CCMouseDispatcher::forceRemoveDelegate(CCMouseDelegate* pDelegate)
{
    CCMouseHandler* pHandler = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pDelegates, pObj)
    {
        pHandler = (CCMouseHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate)
        {
            m_pDelegates->removeObject(pHandler);
            break;
        }
    }
}

bool CCMouseDispatcher::dispatchScrollMSG(float x, float y)
{
    CCMouseHandler*  pHandler = NULL;
    CCMouseDelegate* pDelegate = NULL;

    m_bLocked = true;

    if (m_pDelegates->count() > 0)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pDelegates, pObj)
        {
            CC_BREAK_IF(!pObj);

            pHandler = (CCMouseHandler*)pObj;
            pDelegate = pHandler->getDelegate();

            pDelegate->scrollWheel(x, y);
        }
    }

    m_bLocked = false;
    if (m_bToRemove)
    {
        m_bToRemove = false;
        for (unsigned int i = 0; i < m_pHandlersToRemove->num; ++i)
        {
            forceRemoveDelegate((CCMouseDelegate*)m_pHandlersToRemove->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersToRemove);
    }

    if (m_bToAdd)
    {
        m_bToAdd = false;
        for (unsigned int i = 0; i < m_pHandlersToAdd->num; ++i)
        {
            forceAddDelegate((CCMouseDelegate*)m_pHandlersToAdd->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersToAdd);
    }

    return true;
}

NS_CC_END

CC_GD_ADD_END
