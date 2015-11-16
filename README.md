EasyJNI
=======

After hours of struggling with small bugs in JNI code I got tired and wrote these variadic template wrappers for cocos2d-x JniHelper to make calling Java from C++ nice and easy

Here's an example. Suppose we have a Java class

```java
class Logger {
	public static void purchase(float sum, String currency) {
		// some code here
	}
}
```

Then we can call it from C++ with just one line of code

```cpp
EasyJNI::callStaticVoidMethod("path/to/Logger", "purchase", float(3.14), "USD");
```

There can be any number of arguments and the method signature is automatically inferred under the hood with template magic. Supported argument data types are: bool, char, short, int, long, float, double, char* and std::string. Make sure the arguments on the Java side have corresponding primitive types (no Boolean, Integer, etc), except for char* and std::string, corresponding Java type for them is String. 


One thing to note is that it should be obvious for the compiler to infer template types, otherwise incorrect signature might be generated and JNI won't be able to find the method you are trying to call. This can be achieved with three different approaches:

* Using variables as parameters, i.e.
```cpp
float sum = 3.14;
std::string currency = "USD";
EasyJNI::callStaticVoidMethod("path/to/Logger", "purchase", sum, currency);
```

* With implicit casts:
```cpp
EasyJNI::callStaticVoidMethod("path/to/Logger", "purchase", float(3.14), "USD");
```

* And with implicit template instantiation 
```cpp
EasyJNI::callStaticVoidMethod<float, std::string>("path/to/Logger", "purchase", 3.14, "USD");
```

If the user tries to call Java method with unsupported argument, say CCSprite*, a compile time error will occur, providing the caller with a clear message. If a nonexsitent Java method is called, the error occurs in runtime and the description can be found in logcat output using "EasyJNI" tag. For debugging purposes one may want to add some popup messages instead of log records to EasyJNI::reportError method.