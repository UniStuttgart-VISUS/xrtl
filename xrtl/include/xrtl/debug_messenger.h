// <copyright file="debug_messenger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_DEBUG_MESSENGER_H)
#define _XRTL_DEBUG_MESSENGER_H
#pragma once

#include <cassert>
#include <memory>
#include <stdexcept>

#include "xrtl/debug_policy.h"
#include "xrtl/initialise.h"
#include "xrtl/result.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Facilitates the creation of the OpenXR debug layer.
/// </summary>
/// <typeparam name="Policy">Configures how the messenger behaves if it cannot
/// create the underlying API object.</typeparam>
template<debug_policy Policy> class debug_messenger final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="instance">The OpenXR instance to create the messenger from.
    /// </param>
    /// <param name="create_info">The configuration of the messenger.</param>
    debug_messenger(_In_ XrInstance instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <typeparam name="TCallback">The type of the callback functor.
    /// </typeparam>
    /// <param name="instance">The OpenXR instance to create the messenger from.
    /// </param>
    /// <param name="callback">The callback to be invoked if a message was
    /// received.</param>
    /// <param name="severities">The message severities to be reported.</param>
    /// <param name="types">The message types to be reported.</param>
    /// <param name="context">A context pointer to be passed to the
    /// <paramref name="callback" />.</param>
    template<class TCallback> debug_messenger(_In_ XrInstance instance,
        _In_ const TCallback& callback,
        _In_ const XrDebugUtilsMessageSeverityFlagsEXT severities,
        _In_ const XrDebugUtilsMessageTypeFlagsEXT types,
        _In_ void *context = nullptr);

    debug_messenger(const debug_messenger&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~debug_messenger(void) noexcept;

    debug_messenger& operator =(const debug_messenger&) = delete;

private:

    inline void create(_In_ XrInstance instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info);

    inline PFN_xrCreateDebugUtilsMessengerEXT load(
        _In_ XrInstance instance);

    PFN_xrDestroyDebugUtilsMessengerEXT _destroy;
    XrDebugUtilsMessengerEXT _handle;
};


/// <summary>
/// The default debug severities used by the factory functions.
/// </summary>
constexpr XrDebugUtilsMessageSeverityFlagsEXT default_debug_severities
    = XR_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
    | XR_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
    | XR_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
    | XR_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;


/// <summary>
/// The default message types enabled by the factory functions.
/// </summary>
constexpr XrDebugUtilsMessageTypeFlagsEXT default_debug_types
    = XR_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
    | XR_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
    | XR_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
    | XR_DEBUG_UTILS_MESSAGE_TYPE_CONFORMANCE_BIT_EXT;


/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="Policy">Configures how the messenger behaves if it cannot
/// create the underlying API object.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="create_info">The configuration of the messenger.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<debug_policy Policy>
inline std::unique_ptr<debug_messenger<Policy>> make_debug_messenger(
        _In_ XrInstance instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info) {
    return std::make_unique<debug_messenger<Policy>>(instance, create_info);
}

/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="Policy">Configures how the messenger behaves if it cannot
/// create the underlying API object.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="create_info">The configuration of the messenger.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<debug_policy Policy>
inline std::unique_ptr<debug_messenger<Policy>> make_debug_messenger(
        _In_ unique_instance instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info) {
    return std::make_unique<debug_messenger<Policy>>(instance.get(),
        create_info);
}

/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="Policy">Configures how the messenger behaves if it cannot
/// create the underlying API object.</typeparam>
/// <typeparam name="TCallback">The type of the callback functor.</typeparam>
/// <typeparam name="TContext">The type of a context pointer to be passed to
/// <typeparamref name="TCallback" />.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="callback">The callback to be invoked if a message was received.
/// </param>
/// <param name="severities">The message severities to be reported.</param>
/// <param name="types">The message types to be reported.</param>
/// <param name="context">A context pointer to be passed to the
/// <paramref name="callback" />.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<debug_policy Policy, class TCallback, class TContext>
inline std::unique_ptr<debug_messenger<Policy>> make_debug_messenger(
        _In_ XrInstance instance,
        _In_ const TCallback& callback,
        _In_ const XrDebugUtilsMessageSeverityFlagsEXT severities
            = default_debug_severities,
        _In_ const XrDebugUtilsMessageTypeFlagsEXT types
            = default_debug_types,
        _In_ TContext *context = nullptr) {
    return std::make_unique<debug_messenger<Policy>>(instance, callback,
        severities, types, context);
}

/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="Policy">Configures how the messenger behaves if it cannot
/// create the underlying API object.</typeparam>
/// <typeparam name="TCallback">The type of the callback functor.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="callback">The callback to be invoked if a message was received.
/// </param>
/// <param name="severities">The message severities to be reported.</param>
/// <param name="types">The message types to be reported.</param>
/// <param name="context">A context pointer to be passed to the
/// <paramref name="callback" />.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<debug_policy Policy, class TCallback>
inline std::unique_ptr<debug_messenger<Policy>> make_debug_messenger(
        _In_ const unique_instance& instance,
        _In_ const TCallback& callback,
        _In_ const XrDebugUtilsMessageSeverityFlagsEXT severities
            = default_debug_severities,
        _In_ const XrDebugUtilsMessageTypeFlagsEXT types
            = default_debug_types,
        _In_ void *context = nullptr) {
    return std::make_unique<debug_messenger<Policy>>(instance.get(), callback,
        severities, types, context);
}

/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="TInstance">The type of the OpenXR instance, which can
/// either be a native <c>XrInstance</c> or a unique handle for it.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="create_info">The configuration of the messenger.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<class TInstance>
inline std::unique_ptr<debug_messenger<debug_policy::required>>
make_mandatory_debug_messenger(_In_ TInstance&& instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info) {
    return make_debug_messenger<debug_policy::required>(
        std::forward<TInstance>(instance), create_info);
}

/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="TInstance">The type of the OpenXR instance, which can
/// either be a native <c>XrInstance</c> or a unique handle for it.</typeparam>
/// <typeparam name="TCallback">The type of the callback functor.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="callback">The callback to be invoked if a message was received.
/// </param>
/// <param name="severities">The message severities to be reported.</param>
/// <param name="types">The message types to be reported.</param>
/// <param name="context">A context pointer to be passed to the
/// <paramref name="callback" />.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<class TInstance, class TCallback>
inline std::unique_ptr<debug_messenger<debug_policy::required>>
make_mandatory_debug_messenger(_In_ TInstance&& instance,
        _In_ TCallback&& callback,
        _In_ const XrDebugUtilsMessageSeverityFlagsEXT severities
            = default_debug_severities,
        _In_ const XrDebugUtilsMessageTypeFlagsEXT types
            = default_debug_types,
        _In_ void *context = nullptr) {
    return make_debug_messenger<debug_policy::required>(
        std::forward<TInstance>(instance),
        std::forward<TCallback>(callback),
        severities,
        types,
        context);
}

/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="TInstance">The type of the OpenXR instance, which can
/// either be a native <c>XrInstance</c> or a unique handle for it.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="create_info">The configuration of the messenger.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<class TInstance>
inline std::unique_ptr<debug_messenger<debug_policy::optional>>
make_optional_debug_messenger(_In_ TInstance&& instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info) {
    return make_debug_messenger<debug_policy::optional>(
        std::forward<TInstance>(instance), create_info);
}

/// <summary>
/// Creates a debug messenger for the given OpenXR instance.
/// </summary>
/// <typeparam name="TInstance">The type of the OpenXR instance, which can
/// either be a native <c>XrInstance</c> or a unique handle for it.</typeparam>
/// <typeparam name="TCallback">The type of the callback functor.</typeparam>
/// <param name="instance">The OpenXR instance to create the messenger from.
/// </param>
/// <param name="callback">The callback to be invoked if a message was received.
/// </param>
/// <param name="severities">The message severities to be reported.</param>
/// <param name="types">The message types to be reported.</param>
/// <param name="context">A context pointer to be passed to the
/// <paramref name="callback" />.</param>
/// <returns>A debug messenger with the given configuration.</returns>
template<class TInstance, class TCallback>
inline std::unique_ptr<debug_messenger<debug_policy::optional>>
make_optional_debug_messenger(_In_ TInstance&& instance,
        _In_ TCallback&& callback,
        _In_ const XrDebugUtilsMessageSeverityFlagsEXT severities
            = default_debug_severities,
        _In_ const XrDebugUtilsMessageTypeFlagsEXT types
            = default_debug_types,
        _In_ void *context = nullptr) {
    return make_debug_messenger<debug_policy::optional>(
        std::forward<TInstance>(instance),
        std::forward<TCallback>(callback),
        severities,
        types,
        context);
}

XRTL_NAMESPACE_END

#include "xrtl/debug_messenger.inl"

#endif /* !defined(_XRTL_DEBUG_MESSENGER_H) */
