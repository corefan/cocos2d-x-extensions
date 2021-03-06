
#ifndef __CC_EXTENSION_CCHTTP_REQUEST_H_
#define __CC_EXTENSION_CCHTTP_REQUEST_H_

#include "cocos2dx_extensions.h"
#include "CCHttpRequestDelegate.h"

NS_CC_EXT_BEGIN

typedef enum {
    CCHttpRequestMethodGET = 0,
    CCHttpRequestMethodPOST,
} CCHttpRequestMethod;

class CCHttpRequest : public cocos2d::CCObject
{
public:
    static CCHttpRequest* createWithUrl(CCHttpRequestDelegate* delegate,
                                        const char* url,
                                        CCHttpRequestMethod method = CCHttpRequestMethodGET,
                                        bool isAutoReleaseOnFinish = true);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static CCHttpRequest* createWithUrlLua(cocos2d::LUA_FUNCTION listener,
                                           const char* url,
                                           CCHttpRequestMethod method = CCHttpRequestMethodGET);
#endif
    
    ~CCHttpRequest(void);
    
    /** @brief Add a custom header to the request. */
    void addRequestHeader(const char* key, const char* value);
    
    /** @brief Add a POST variable to the request, POST only. */
    void addPostValue(const char* key, const char* value);
    
    /** @brief Number of seconds to wait before timing out - default is 10. */
    void setTimeout(float timeout);
    float getTimeout(void);
    
    /** @brief True when the request hasn't finished yet. */
    bool getIsInProgress(void);
    
    /** @brief Eexecute an asynchronous request
     
     If isCached set to false, it will force request not to be cached.        
     Setting isCache to false also appends a query string parameter, "_=[TIMESTAMP]", to the URL.
     */
    void start(bool isCached = false);
    
    /** @brief Cancel an asynchronous request. */
    void cancel(void);
    
    /** @brief Cancel an asynchronous request, clearing all delegates first. */
    void clearDelegatesAndCancel(void);
    
    /** @brief Returns the contents of the result. */
    const char* getResponseString(void);
    
    /** @brief Response data. */
    const void* getResponseData(int* dataLength);
    
private:
    CCHttpRequest(CCHttpRequestDelegate* delegate, const char* url, CCHttpRequestMethod method, bool isAutoReleaseOnFinish)
    : m_delegate(delegate)
    , m_url(url ? url : "")
    , m_method(method)
    , m_request(NULL)
    , m_responseData(NULL)
    , m_responseDataLength(0)
    , m_isAutoReleaseOnFinish(isAutoReleaseOnFinish)
#if CC_LUA_ENGINE_ENABLED > 0
    , m_luaListener(0)
#endif
    {
    }
    bool initHttpRequest(void);
    
    CCHttpRequestDelegate*  m_delegate;
    const std::string       m_url;
    CCHttpRequestMethod     m_method;
    void*                   m_request;
    void*                   m_responseData;
    int                     m_responseDataLength;
    std::string             m_responseString;
    bool                    m_isAutoReleaseOnFinish;
#if CC_LUA_ENGINE_ENABLED > 0
    cocos2d::LUA_FUNCTION   m_luaListener;
#endif
};

NS_CC_EXT_END

#endif // __CC_EXTENSION_CCHTTP_REQUEST_H_
