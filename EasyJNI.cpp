#include "EasyJNI.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "base/ccUTF8.h"

#define LOG_TAG "EasyJNI"
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

std::unordered_map<JNIEnv*, std::vector<jobject>> EasyJNI::localRefs;

jstring EasyJNI::convert(cocos2d::JniMethodInfo& t, const char* x) {
    jstring ret = cocos2d::StringUtils::newStringUTFJNI(t.env, x ? x : "");
    localRefs[t.env].push_back(ret);
    return ret;
}

jstring EasyJNI::convert(cocos2d::JniMethodInfo& t, const std::string& x) {
    return convert(t, x.c_str());
}

void EasyJNI::deleteLocalRefs(JNIEnv* env) {
    if (!env) {
        return;
    }

    for (const auto& ref : localRefs[env]) {
        env->DeleteLocalRef(ref);
    }
    localRefs[env].clear();
}

void EasyJNI::reportError(const std::string& className, const std::string& methodName, const std::string& signature) {
    LOGE("Failed to find static java method. Class name: %s, method name: %s, signature: %s ",  className.c_str(), methodName.c_str(), signature.c_str());
}

#endif