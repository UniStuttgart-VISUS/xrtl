// <copyright file="initialise.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_INITIALISE_H)
#define _XRTL_INITIALISE_H
#pragma once

#include <cstring>

#include "xrtl/xr_type_traits.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Initialises an OpenXR API structure by zeroing everything and setting the
/// <c>type</c> member.
/// </summary>
/// <typeparam name="TValue">The type of the structure.</typeparam>
/// <param name="value">The stucuture to be initialised.</param>
/// <returns><paramref name="value" /></returns>
template<class TValue>
inline TValue& initialise_xrstruct(_Out_ TValue& value) noexcept {
    ::memset(&value, 0, sizeof(value));
    value.type = xr_type_traits<TValue>::value;
    return value;
}

/// <summary>
/// Initialises an OpenXR API structure by zeroing everything and setting the
/// <c>type</c> member.
/// </summary>
/// <typeparam name="TValue">The type of the structure.</typeparam>
/// <param name="value">The stucuture to be initialised.</param>
/// <returns><paramref name="value" /></returns>
template<class TValue>
inline TValue& init_xrstruct(_Out_ TValue& value) noexcept {
    return initialise_xrstruct(value);
}

/// <summary>
/// Initialise a new OpenXR API structure of the specified type by zeroing
/// everything and setting the <c>type</c> member.
/// </summary>
/// <typeparam name="TValue">The type of the structure.</typeparam>
/// <returns>The initialises structure</returns>
template<class TValue> inline TValue initialise_xrstruct(void) noexcept {
    TValue retval;
    return initialise_xrstruct(retval);
}

/// <summary>
/// Initialise a new OpenXR API structure of the specified type by zeroing
/// everything and setting the <c>type</c> member.
/// </summary>
/// <typeparam name="TValue">The type of the structure.</typeparam>
/// <returns>The initialises structure</returns>
template<class TValue> inline TValue init_xrstruct(void) noexcept {
    return initialise_xrstruct<TValue>();
}

XRTL_NAMESPACE_END

#endif /* !defined(_XRTL_INITIALISE_H) */
