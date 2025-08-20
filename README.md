# XR Template Library
A header-only library for managing OpenXR resources.

## Error handling
The library provides a custom error category for `std::system_error` to treat OpenXR failures are system errors. The error category will always work, but in order to produce meaningful messages, it needs access to the `XrInstance`. Once you have the instance, call
```c++
xrtl::xr_category_instance(instance);
```
and unregister it by calling it with `XR_NULL_HANDLE` before freeing the instance.

Afterwards, error handling can be performed by wrapping calls with the `THROW_IF_XR_FAILED` or `THROW_IF_XR_FAILED_MSG` macros:
```c++
THROW_IF_XR_FAILED(::xrCreateSession(instance, &ci, &session));
THROW_IF_XR_FAILED_MSG(::xrCreateSession(instance, &ci, &session), "Failed to create an OpenXR session.");
```

## Resource management
`xrtl::unique_handle` provides a means to automatically release OpenXR resources. There are `typedef`s for the most commonly used handles. For instance, the OpenXR session can be managed like this:
```c++
auto ci = xrtl::init_xrstruct<XrInstanceCreateInfo>();
//...

xrtl::unique_instance instance;
THROW_IF_XR_FAILED_MSG(::xrCreateInstance(&ci, instance.put()), "Failed to create OpenXR instance.");
```

## Debug layer
The `debug_messenger` class is an RAII wrapper for the OpenXR debug layer. It will load the necessary extension functions and create the debug messenger on construction and free it when its destructor is called. The `debug_messenger` comes with two policies, one marking it as optional, the other marking it as required. In optional mode, the class will fail silently if it cannot load the extension functions or the messenger cannot be created. In required mode, it will throw on the first error. Using one of the factory functions, a messenger in required mode can be created like this:
```c++
auto dbg_msg = xrtl::make_mandatory_debug_messenger(instance,
    [](XrDebugUtilsMessageSeverityFlagsEXT severity, XrDebugUtilsMessageTypeFlagsEXT types, const XrDebugUtilsMessengerCallbackDataEXT *msg, void *user_data) {
        std::cout << msg->functionName << ": " << msg->message << std::endl;
        return static_cast<XrBool32>(XR_FALSE);
    });
```
