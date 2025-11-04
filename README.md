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

## Maths interoperability
The library provides functions for converting OpenXR maths types to [DirectX Math](https://github.com/microsoft/DirectXMath) and [glm](https://github.com/g-truc/glm). The former is available on Windows only, the latter requires `XRTL_WITH_GLM` to be defined in the application.

### DirectX Math
```c++
#include <xrtl/xmath.h>

// Load an OpenXR vector.
XrVector4f xr = { 1.0f, 2.0f, 3.0f, 4.0f };
DirectX::XMVECTOR xm = xrtl::load_xmvector(xr);

// Do things with the DirectX Math library.

// Return the result.
xrtl::store_xmvector(xr, xm);

// Loading is also supported for OpenXR poses.
XrPosef pose;
pose.position.x = 1.0f;
pose.position.y = 0.0f;
pose.position.z = 0.0f;
pose.orientation.x = 0.0f;
pose.orientation.y = 0.5f * ::sqrt(2.0f);
pose.orientation.z = 0.0f;
pose.orientation.w = pose.orientation.y;

DirectX::XMMATRIX view_matrix = xrtl::load_xmmatrix(pose);
```

### GLM
```c++
#define XRTL_WITH_GLM
#include <xrtl/glm.h>

// Load an OpenXR vector.
XrVector4f xr = { 1.0f, 2.0f, 3.0f, 4.0f };
glm::vec4 gl = xrtl::to_glm(xr);

// Do things with GLM.

// Return the result.
xr = xrtl::from_glm(gl);

// Loading is also supported for OpenXR poses.
XrPosef pose;
pose.position.x = 1.0f;
pose.position.y = 0.0f;
pose.position.z = 0.0f;
pose.orientation.x = 0.0f;
pose.orientation.y = 0.5f * ::sqrt(2.0f);
pose.orientation.z = 0.0f;
pose.orientation.w = pose.orientation.y;

glm::mat view_matrix = xrtl::to_glm(pose);
```

### Projection matrix
A projection matrix can be derived from `XrFovf` by providing a conversion from the typical input of functions building off-centre projection matrices like `DirectX::XMMatrixPerspectiveOffCenterRH` and `glm::frustumRH_ZO<float>`. The following two examples create the same right-handed projection matrix using a Direct3D-style z-range:
```c++
#include <DirectXMath.h>
#include <xrtl/matrix.h>

constexpr auto near_plane = 0.1f;
constexpr auto far_plane = 100.0f;

XrFovf fov;
fov.angleLeft = -0.5f;
fov.angleRight = 0.5f;
fov.angleUp = 0.5f;
fov.angleDown = -0.5f;

auto proj_matrix = xrtl::make_matrix(DirectX::XMMatrixPerspectiveOffCenterRH, fov, near_plane, far_plane);
```

```c++
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <xrtl/matrix.h>

constexpr auto near_plane = 0.1f;
constexpr auto far_plane = 100.0f;

XrFovf fov;
fov.angleLeft = -0.5f;
fov.angleRight = 0.5f;
fov.angleUp = 0.5f;
fov.angleDown = -0.5f;

// Note: be sure to instantiate the GLM template here, because this cannot be deduced.
auto proj_matrix = xrtl::make_matrix(glm::frustumRH_ZO<float>, fov, near_plane, far_plane);
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
