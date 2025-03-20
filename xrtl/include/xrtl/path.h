// <copyright file="path.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_PATH_H)
#define _XRTL_PATH_H
#pragma once

#include <cassert>
#include <cinttypes>
#include <string>

#include <openxr/openxr.h>

#include "xrtl/result.h"
#include "xrtl/unique_handle.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Wraps an <see cref="XrPath" />.
/// </summary>
class path final {

public:

    /// <summary>
    /// Parses the given OpenXR path from its string representation.
    /// </summary>
    /// <param name="instance">The OpenXR instance used to perform the
    /// conversion.</param>
    /// <param name="path">The string representation of the path.</param>
    /// <returns>The OpenXR path represented by the given string.</returns>
    /// <exception cref="std::system_error">If the operation failed.</exception>
    static inline XrPath parse(_In_ const XrInstance instance,
            _In_z_ const char *path) {
        assert(instance != XR_NULL_HANDLE);
        assert(path != nullptr);
        XrPath retval;
        THROW_IF_XR_FAILED(::xrStringToPath(instance, path, &retval));
        return retval;
    }

    /// <summary>
    /// Parses the given OpenXR path from its string representation.
    /// </summary>
    /// <param name="instance">The OpenXR instance used to perform the
    /// conversion.</param>
    /// <param name="path">The string representation of the path.</param>
    /// <returns>The OpenXR path represented by the given string.</returns>
    /// <exception cref="std::system_error">If the operation failed.</exception>
    static inline XrPath parse(_In_ const unique_instance& instance,
            _In_z_ const char *path) {
        return parse(instance.get(), path);
    }

    /// <summary>
    /// Initialsies a new instance.
    /// </summary>
    inline path(void) noexcept : _path(XR_NULL_PATH) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="instance">The OpenXR instance used to perform the
    /// conversion.</param>
    /// <param name="path">The string representation of the path.</param>
    /// <exception cref="std::system_error">If the path could not be parsed from
    /// the given input.</exception>
    inline path(_In_ const XrInstance instance, _In_z_ const char *path)
        : _path(parse(instance, path)) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="instance">The OpenXR instance used to perform the
    /// conversion.</param>
    /// <param name="path">The string representation of the path.</param>
    /// <exception cref="std::system_error">If the path could not be parsed from
    /// the given input.</exception>
    inline path(_In_ const unique_instance& instance, _In_z_ const char *path)
        : _path(parse(instance, path)) {}

    /// <summary>
    /// Answer whether the path is invalid.
    /// </summary>
    /// <returns><c>true</c> if the path is not valid, <c>false</c> if it is
    /// something other than <c>XR_NULL_PATH</c>.</returns>
    inline bool empty(void) const noexcept {
        return (this->_path == XR_NULL_PATH);
    }

    /// <summary>
    /// Convert the path back to its string representation.
    /// </summary>
    /// <param name="instance">The OpenXR instance used to perform the
    /// conversion.</param>
    /// <returns>The string representation of the path.</returns>
    inline std::string to_string(_In_ const XrInstance instance) {
        assert(instance != XR_NULL_HANDLE);
        std::uint32_t len = XR_MAX_PATH_LENGTH;
        char retval[XR_MAX_PATH_LENGTH];
        THROW_IF_XR_FAILED(::xrPathToString(instance,
            this->_path,
            len,
            &len,
            retval));
        return std::string(retval, retval + len);
    }

    /// <summary>
    /// Convert the path back to its string representation.
    /// </summary>
    /// <param name="instance">The OpenXR instance used to perform the
    /// conversion.</param>
    /// <returns>The string representation of the path.</returns>
    inline std::string to_string(_In_ const unique_instance& instance) {
        return this->to_string(instance.get());
    }

    /// <summary>
    /// Gets the native <see cref="XrPath" />.
    /// </summary>
    /// <returns>The native XrPath.</returns>
    inline XrPath get(void) const noexcept {
        return this->_path;
    }

    /// <summary>
    /// Gets the native <see cref="XrPath" />.
    /// </summary>
    /// <returns>The native XrPath.</returns>
    inline operator XrPath(void) const noexcept {
        return this->_path;
    }

    /// <summary>
    /// Answer whether the path is valid.
    /// </summary>
    /// <returns><c>true</c> if the path is valid, <c>false</c> if it is a
    /// <c>XR_NULL_PATH</c>.</returns>
    inline operator bool(void) const noexcept {
        return (this->_path != XR_NULL_PATH);
    }

private:

    XrPath _path;
};

XRTL_NAMESPACE_END

#endif /* !defined(_XRTL_PATH_H) */
