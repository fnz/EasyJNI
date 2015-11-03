#include "EasyJNI.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

namespace easyjni {

std::string getJNISignature() {
    return "";
}

template <>
std::string getJNISignature(bool) {
    return "Z";
}

template <>
std::string getJNISignature(char) {
    return "C";
}

template <>
std::string getJNISignature(short) {
    return "S";
}

template <>
std::string getJNISignature(int) {
    return "I";
}

template <>
std::string getJNISignature(long) {
    return "J";
}

template <>
std::string getJNISignature(float) {
    return "F";
}

template <>
std::string getJNISignature(double) {
    return "D";
}

template <>
std::string getJNISignature(const char*) {
    return "Ljava/lang/String;";
}

template <>
std::string getJNISignature(std::string) {
    return "Ljava/lang/String;";
}

jstring convert(cocos2d::JniMethodInfo& t, const char* x) {
    return t.env->NewStringUTF(x);
}

jstring convert(cocos2d::JniMethodInfo& t, std::string x) {
    return t.env->NewStringUTF(x.c_str());
}
}

#endif