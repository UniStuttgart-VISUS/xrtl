// <copyright file="unique_handle.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_UNIQUE_HANDLE_H)
#define _XRTL_UNIQUE_HANDLE_H
#pragma once

#include <memory>

#include <openxr/openxr.h>

#include "xrtl/api.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// RAII container for OpenXR handles.
/// </summary>
/// <typeparam name="THandle">The native type of the handle.</typeparam>
/// <typeparam name="TDelete">The type of the deleter function.</typeparam>
template<class THandle, XrResult (*TDelete)(THandle)>
class unique_handle final {

public:

    /// <summary>
    /// The native type of the handle.
    /// </summary>
    typedef THandle handle_type;

    /// <summary>
    /// Initialises a new instance by taking ownership of the given
    /// <paramref name="handle "/>.
    /// </summary>
    /// <param name="handle">The handle to be moved into the RAII object.
    /// </param>
    inline unique_handle(_In_opt_ handle_type handle = XR_NULL_HANDLE) noexcept
        : _handle(handle) { }

    /// <summary>
    /// Move <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline unique_handle(_Inout_ unique_handle&& rhs) noexcept
            : _handle(rhs._handle) {
        rhs._handle = XR_NULL_HANDLE;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~unique_handle(void) noexcept {
        this->reset();
    }

    /// <summary>
    /// Gets the native handle.
    /// </summary>
    /// <returns>The native handle.</returns>
    inline handle_type get(void) const noexcept {
        return this->value;
    }

    /// <summary>
    /// Releases any existing value and exposes a pointer to the native handle
    /// for use as out parameter in an API call.
    /// </summary>
    /// <returns>A pointer to the native handle.</returns>
    inline handle_type *put(void) noexcept {
        this->reset();
        return std::addressof(this->_handle);
    }

    /// <summary>
    /// Relinquishes ownership of the handle and returns it.
    /// </summary>
    /// <returns>The handle, which the caller will take ownership of.</returns>
    handle_type release(void) noexcept {
        auto retval = this->_handle;
        this->_handle = XR_NULL_HANDLE;
        return retval;
    }

    /// <summary>
    /// Releases the existing handle and takes ownership of
    /// <paramref name="handle" />.
    /// </summary>
    /// <param name="handle">The new native handle managed by the object.
    /// </param>
    void reset(_In_opt_ handle_type handle = XR_NULL_HANDLE) noexcept;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    unique_handle& operator =(_Inout_ unique_handle&& rhs) noexcept;

    /// <summary>
    /// Answer whether the handle is valid.
    /// </summary>
    /// <returns><c>true</c> if the handle is valid, <c>false</c> otherwise.
    /// </returns>
    inline operator bool(void) const noexcept {
        return (this->_handle != XR_NULL_HANDLE);
    }

private:

    handle_type _handle;
};


/// <summary>
/// Specialisation for <see cref="XrAction" />.
/// </summary>
typedef unique_handle<XrAction, ::xrDestroyAction> unique_action;

/// <summary>
/// Specialisation for <see cref="XrActionSet" />.
/// </summary>
typedef unique_handle<XrActionSet, ::xrDestroyActionSet> unique_action_set;

/// <summary>
/// Specialisation for <see cref="XrInstance" />.
/// </summary>
typedef unique_handle<XrInstance, ::xrDestroyInstance> unique_instance;

/// <summary>
/// Specialisation for <see cref="XrSpace" />.
/// </summary>
typedef unique_handle<XrSpace, ::xrDestroySpace> unique_space;

/// <summary>
/// Specialisation for <see cref="XrSwapchain" />.
/// </summary>
typedef unique_handle<XrSwapchain, ::xrDestroySwapchain> unique_swap_chain;

XRTL_NAMESPACE_END

#include "xrtl/unique_handle.inl"

#endif /* !defined(_XRTL_UNIQUE_HANDLE_H) */
