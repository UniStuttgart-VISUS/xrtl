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
/// <see cref="XrResult" />.
/// </summary>
/// <param name="r">The <see cref="XrResult" /> used as error code.</param>
/// <param name="m">A custom error message.</param>
#define THROW_XR_RESULT_MSG(r, m)\
throw std::system_error((r), xrtl::xr_category(), (m))


#endif /* !defined(_XRTL_RESULT_H) */
