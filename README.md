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
easyjni::callVoidMethod("path/to/Logger", "purchase", 3.14, "USD");
```

There can be any number of arguments and the method signature is automatically inferred under the hood with template magic. Supported argument data types are: bool, char, short, int, long, float, double, char* and std::string. Make sure the arguments on the Java side have corresponding primitive types (no Boolean, Integer, etc), except for char* and std::string, corresponding Java type for them is String. 



