// <copyright file="xr_type_traits.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_XR_TYPE_TRAITS_H)
#define _XRTL_XR_TYPE_TRAITS_H
#pragma once

#include <string>
#include <system_error>

#include <openxr/openxr.h>

#include "xrtl/api.h"


XRTL_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Actual implementation of the type traits.
/// </summary>
/// <typeparam name="TType">The OpenXR structure described by this trait.
/// </typeparam>
/// <typeparam name="Type">The OpenXR structure type.</typeparam>
template<class TType, XrStructureType Type> struct xrtt_impl {

    /// <summary>
    /// The OpenXR structure described by this trait.
    /// </summary>
    typedef TType type;

    /// <summary>
    /// The OpenXR structure type.
    /// </summary>
    constexpr static const XrStructureType value = Type;
};

XRTL_DETAIL_NAMESPACE_END


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Allows for deriving the <see cref="XrStructureType" /> of an OpenXR stucture
/// from its type.
/// </summary>
/// <remarks>
/// This is the fallback implementation for all unknown types, which will all
/// resolve to <see cref="XR_TYPE_UNKNOWN" />.
/// </remarks>
/// <typeparam name="TType">The OpenXR structure described by this
/// trait.</typeparam>
template<class TType>
struct xr_type_traits : public detail::xrtt_impl<TType, XR_TYPE_UNKNOWN> { };

#include "xrtl/xr_type_traits.inl"

XRTL_NAMESPACE_END

#endif /* !defined(_XRTL_XR_TYPE_TRAITS_H) */
