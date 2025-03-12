// <copyright file="result.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_RESULT_H)
#define _XRTL_RESULT_H
#pragma once

#include "xrtl/xr_error_category.h"


/// <summary>
/// Throw an <see cref="std::system_error" /> representing the given
/// <see cref="XrResult" />.
/// </summary>
/// <param name="r">The <see cref="XrResult" /> used as error code.</param>
#define THROW_XR_RESULT(r) throw std::system_error((r), xrtl::xr_category())

/// <summary>
/// Throw an <see cref="std::system_error" /> representing the given
/// <see cref="XrResult" /> if a certain condition is fulfilled.
/// </summary>
/// <param name="r">The <see cref="XrResult" /> used as error code.</param>
/// <param name="c">The condition that needs to be fulfilled for the exception
/// to be thrown.</param>
#define THROW_XR_RESULT_IF(r, c) if (c) throw std::system_error((r), \
xrtl::xr_category())

/// <summary>
/// Throw an <see cref="std::system_error" /> representing the given
/// <see cref="XrResult" /> if a certain condition is fulfilled.
/// </summary>
/// <param name="r">The <see cref="XrResult" /> used as error code.</param>
/// <param name="c">The condition that needs to be fulfilled for the exception
/// to be thrown.</param>
/// <param name="m">A custom error message.</param>
#define THROW_XR_RESULT_IF_MSG(r, c, m) if (c) throw std::system_error((r), \
xrtl::xr_category(), (m));

/// <summary>
/// Throw an <see cref="std::system_error" /> representing the given
/// <see cref="XrResult" />.
/// </summary>
/// <param name="r">The <see cref="XrResult" /> used as error code.</param>
/// <param name="m">A custom error message.</param>
#define THROW_XR_RESULT_MSG(r, m)\
throw std::system_error((r), xrtl::xr_category(), (m))

/// <summary>
/// Throw an <see cref="std::system_error" /> if the given expression yielding an
/// <see cref="XrResult" /> represents failure.
/// </summary>
/// <param name="e">An expression yielding a <see cref="XrResult" />.</param>
#define THROW_IF_XR_FAILED(e)\
{ auto r = (e); THROW_XR_RESULT_IF(r, XR_FAILED(r)); }

/// <summary>
/// Throw an <see cref="std::system_error" /> if the given expression yielding an
/// <see cref="XrResult" /> represents failure.
/// </summary>
/// <param name="e">An expression yielding a <see cref="XrResult" />.</param>
/// <param name="m">A custom error message.</param>
#define THROW_IF_XR_FAILED_MSG(e, m)\
{ auto r = (e); THROW_XR_RESULT_IF_MSG(r, XR_FAILED(r), (m)); }


#endif /* !defined(_XRTL_RESULT_H) */
