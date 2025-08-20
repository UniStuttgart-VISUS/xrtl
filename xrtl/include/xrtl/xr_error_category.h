// <copyright file="xr_error_category.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_XR_ERROR_CATEGORY_H)
#define _XRTL_XR_ERROR_CATEGORY_H
#pragma once

#include <string>
#include <system_error>

#include <openxr/openxr.h>

#include "xrtl/api.h"
#include "xrtl/unique_handle.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Sets the <paramref name="instance" /> in the OpenXR error category such
/// that the category can retrieve an error string.
/// </summary>
/// <param name="instance">The instance to be set. If you destroy the instance,
/// call the method again with <c>XR_NULL_HANDLE</c>.</param>
inline void xr_category_instance(_In_opt_ XrInstance instance);

/// <summary>
/// Sets the <paramref name="instance" /> in the OpenXR error category such
/// that the category can retrieve an error string.
/// </summary>
/// <param name="instance">The instance to be set. If you destroy the instance,
/// call the method again with <c>XR_NULL_HANDLE</c>.</param>
inline void xr_category_instance(_In_ const unique_instance& instance) {
    xr_category_instance(instance.get());
}

XRTL_NAMESPACE_END


XRTL_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An error category for OpenXR result values.
/// </summary>
/// <typeparam name="TError">The native error code.</typeparam>
template<class TError>
class xr_error_category final : public std::error_category {

public:

    typedef TError value_type;

    using std::error_category::error_category;

    inline xr_error_category(void) : _instance(nullptr) { }

    std::error_condition default_error_condition(
        _In_ const int error) const noexcept override;

    std::string message(_In_ const int error) const override;

    _Ret_z_ const char *name(void) const noexcept override;

private:

    mutable XrInstance _instance;

    friend void xrtl::xr_category_instance(XrInstance);
};


/// <summary>
/// Generates an returns a static <see cref="TCategory" />.
/// </summary>
/// <typeparam name="TCategory"></typeparam>
/// <returns></returns>
template<class TCategory>
_Ret_valid_ inline const TCategory& xr_category(void) noexcept {
    static TCategory retval;
    return retval;
}

XRTL_DETAIL_NAMESPACE_END


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Answer a <see cref="detail::xr_error_category" />.
/// </summary>
/// <returns>The only instance of <see cref="XrErrorCategory" />.
/// </returns>
_Ret_valid_ inline const std::error_category& xr_category(void) noexcept {
    typedef detail::xr_error_category<XrResult> category;
    return detail::xr_category<category>();
}

XRTL_NAMESPACE_END

#include "xrtl/xr_error_category.inl"

#endif /* !defined(_XRTL_XR_ERROR_CATEGORY_H) */
