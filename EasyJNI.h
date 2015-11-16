#pragma once

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "jni.h"
#include "jni/JniHelper.h"
#include "platform/CCPlatformConfig.h"

#include <vector>
#include <unordered_map>

class EasyJNI {
public:
    template <typename... Ts>
    static void callStaticVoidMethod(const std::string& className, const std::string& methodName, Ts... xs) {
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
    }

    template <typename... Ts>
    static bool callStaticBooleanMethod(const std::string& className, const std::string& methodName, Ts... xs) {
        jboolean jret = JNI_FALSE;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Z";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            jret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return (jret == JNI_TRUE);
    }

    template <typename... Ts>
    static int callStaticIntMethod(const std::string& className, const std::string& methodName, Ts... xs) {
        jint ret = 0;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")I";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            ret = t.env->CallStaticIntMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    template <typename... Ts>
    static float callStaticFloatMethod(const std::string& className, const std::string& methodName, Ts... xs) {
        jfloat ret = 0.0;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")F";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    template <typename... Ts>
    static double callStaticDoubleMethod(const std::string& className, const std::string& methodName, Ts... xs) {
        jdouble ret = 0.0;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")D";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, convert(t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    template <typename... Ts>
    static std::string callStaticStringMethod(const std::string& className, const std::string& methodName, Ts... xs) {
        std::string ret;

        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Ljava/lang/String;";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str())) {
            jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(t, xs)...);
            ret = cocos2d::JniHelper::jstring2string(jret);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jret);
            deleteLocalRefs(t.env);
        } else {
            reportError(className, methodName, signature);
        }
        return ret;
    }

private:
    static jstring convert(cocos2d::JniMethodInfo& t, const char* x);

    static jstring convert(cocos2d::JniMethodInfo& t, const std::string& x);

    template <typename T>
    static T convert(cocos2d::JniMethodInfo&, T x) {
        return x;
    }

    static std::unordered_map<JNIEnv*, std::vector<jobject>> localRefs;

    static void deleteLocalRefs(JNIEnv* env);

    static std::string getJNISignature() {
        return "";
    }

    static std::string getJNISignature(bool) {
        return "Z";
    }

    static std::string getJNISignature(char) {
        return "C";
    }

    static std::string getJNISignature(short) {
        return "S";
    }

    static std::string getJNISignature(int) {
        return "I";
    }

    static std::string getJNISignature(long) {
        return "J";
    }

    static std::string getJNISignature(float) {
        return "F";
    }

    static std::string getJNISignature(double) {
        return "D";
    }

    static std::string getJNISignature(const char*) {
        return "Ljava/lang/String;";
    }

    static std::string getJNISignature(const std::string&) {
        return "Ljava/lang/String;";
    }

    template <typename T>
    static std::string getJNISignature(T x) {
        // This template should never be instantiated
        static_assert(sizeof(x) == 0, "Unsupported argument type");
        return "";
    }

    template <typename T, typename... Ts>
    static std::string getJNISignature(T x, Ts... xs) {
        return getJNISignature(x) + getJNISignature(xs...);
    }

    static void reportError(const std::string& className, const std::string& methodName, const std::string& signature);
};

#endif