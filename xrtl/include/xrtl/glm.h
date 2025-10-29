// <copyright file="xmath.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_GLM_H)
#define _XRTL_GLM_H
#pragma once

#if defined(XRTL_WITH_GLM)
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <openxr/openxr.h>

#include "xrtl/api.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Stores a GLM 2D vector into an OpenXR vector.
/// </summary>
/// <param name="v">The GLM vector to load.</param>
/// <returns>The equivalent OpenXR vector.</returns>
inline constexpr XrVector2f from_glm(_In_ const glm::vec2& v) noexcept {
    return XrVector2f { v.x, v.y };
}


/// <summary>
/// Stores a GLM 3D vector into an OpenXR vector.
/// </summary>
/// <param name="v">The GLM vector to load.</param>
/// <returns>The equivalent OpenXR vector.</returns>
inline constexpr XrVector3f from_glm(_In_ const glm::vec3& v) noexcept {
    return XrVector3f { v.x, v.y, v.z };
}


/// <summary>
/// Stores a GLM 4D vector into an OpenXR vector.
/// </summary>
/// <param name="v">The GLM vector to load.</param>
/// <returns>The equivalent OpenXR vector.</returns>
inline constexpr XrVector4f from_glm(_In_ const glm::vec4& v) noexcept {
    return XrVector4f { v.x, v.y, v.z, v.w };
}


/// <summary>
/// Stores a GLM quaternion into an OpenXR 3D quaternion.
/// </summary>
/// <param name="v">The GLM quaternion to load.</param>
/// <returns>The equivalent OpenXR quaternion.</returns>
inline constexpr XrQuaternionf from_glm(_In_ const glm::quat& q) noexcept {
    return XrQuaternionf { q.x, q.y, q.z, q.w };
}


/// <summary>
/// Loads an OpenXR 2D vector into a GLM vector.
/// </summary>
/// <param name="v">The OpenXR vector to load.</param>
/// <returns>The equivalent GLM vector.</returns>
inline constexpr glm::vec2 to_glm(_In_ const XrVector2f &v) noexcept {
    return glm::vec2(v.x, v.y);
}


/// <summary>
/// Loads an OpenXR 3D vector into a GLM vector.
/// </summary>
/// <param name="v">The OpenXR vector to load.</param>
/// <returns>The equivalent GLM vector.</returns>
inline constexpr glm::vec3 to_glm(_In_ const XrVector3f& v) noexcept {
    return glm::vec3(v.x, v.y, v.z);
}


/// <summary>
/// Loads an OpenXR 4D vector into a GLM vector.
/// </summary>
/// <param name="v">The OpenXR vector to load.</param>
/// <returns>The equivalent GLM vector.</returns>
inline constexpr glm::vec4 to_glm(_In_ const XrVector4f& v) noexcept {
    return glm::vec4(v.x, v.y, v.z, v.w);
}


/// <summary>
/// Loads an OpenXR quaternion into a GLM quaternion.
/// </summary>
/// <param name="v">The OpenXR quaternion to load.</param>
/// <returns>The equivalent GLM quaternion.</returns>
inline constexpr glm::quat to_glm(_In_ const XrQuaternionf& q) noexcept {
    return glm::quat(q.w, q.x, q.y, q.z);
}


/// <summary>
/// Loads an OpenXR pose into a GLM matrix.
/// </summary>
/// <param name="p">The pose to be transformed.</param>
/// <returns>The GLM matrix representing the given pose.</returns>
inline glm::mat4 to_glm(_In_ const XrPosef& p) noexcept {
    const auto r = to_glm(p.orientation);
    const auto t = to_glm(p.position);
    auto retval = glm::mat4_cast(r);
    retval[3] += glm::vec4(t, 0.0f);
    return retval;
}

XRTL_NAMESPACE_END

#endif /* defined(XRTL_WITH_GLM) */

#endif /* !defined(_XRTL_GLM_H) */
