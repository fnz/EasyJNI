#pragma once

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "jni.h"
#include "jni/JniHelper.h"

namespace easyjni {

std::string getJNISignature();

template <typename T, typename... Ts>
std::string getJNISignature(T x, Ts... xs) {
    return getJNISignature(x) + getJNISignature(xs...);
}

jstring convert(cocos2d::JniMethodInfo& t, const char* x);

jstring convert(cocos2d::JniMethodInfo& t, std::string x);

template <typename T>
T convert(cocos2d::JniMethodInfo&, T x) {
    return x;
}

template <typename... Ts>
void callStaticVoidMethod(const std::string& className, const std::string& methodName, Ts... xs) {
    cocos2d::JniMethodInfo t;
    std::string signature = "(" + getJNISignature(xs...) + ")V";
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, convert(t, xs)...);
        t.env->DeleteLocalRef(t.classID);
    }
}

template <typename... Ts>
std::string callStaticStringMethod(const std::string& className, const std::string& methodName, Ts... xs) {
    std::string ret;

    cocos2d::JniMethodInfo t;
    std::string signature = "(" + getJNISignature(xs...) + ")Ljava/lang/String;";
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
        jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(t, xs)...);
        ret = cocos2d::JniHelper::jstring2string(jret);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jret);
    }
    return ret;
}

template <typename... Ts>
bool callStaticBooleanMethod(const std::string& className, const std::string& methodName, Ts... xs) {
    jboolean jret = JNI_FALSE;
    cocos2d::JniMethodInfo t;
    std::string signature = "(" + getJNISignature(xs...) + ")Z";
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
        jret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, convert(t, xs)...);
        t.env->DeleteLocalRef(t.classID);
    }
    return (jret == JNI_TRUE);
}
}

#endif