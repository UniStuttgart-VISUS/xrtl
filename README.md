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
