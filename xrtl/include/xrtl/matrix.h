// <copyright file="matrix.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_MATRIX_H)
#define _XRTL_MATRIX_H
#pragma once

#include <cassert>
#include <cmath>
#include <stdexcept>

#include <openxr/openxr.h>

#include "xrtl/api.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Creates a projection matrix using the given OpenXR field of view and the
/// clipping range between <see cref="near_plane" /> and
/// <see cref="far_plane" />.
/// </summary>
/// <typeparam name="TBuilder">The type of the function or lambda making an
/// off-centre matrix, which must be something like <c>glm::frustumRH_ZO</c>
/// or <c>XMMatrixPerspectiveOffCenterRH</c>. It is expected to accept the
/// left, right, bottom and top extents of the near plane and the distance to
/// the near and far plane as inputs, in that order.</typeparam>
/// <param name="builder">The builder function creating the matrix.</param>
/// <param name="fov">The field of view from OpenXR.</param>
/// <param name="near_plane">The distance to the near clipping plane, which
/// must be positive.</param>
/// <param name="far_plane">The distance to the far clipping plane.</param>
/// <returns>The projection matrix created by the <paramref name="builder" />.
/// </returns>
template<class TBuilder> auto make_matrix(
    _In_ const TBuilder& builder,
    _In_ const XrFovf& fov,
    _In_ const float near_plane,
    _In_ const float far_plane)
    -> decltype(builder(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));

XRTL_NAMESPACE_END

#include "xrtl/matrix.inl"


#endif /* !defined(_XRTL_MATRIX_H) */
