// <copyright file="xmath.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_XMATH_H)
#define _XRTL_XMATH_H
#pragma once

#if defined(_WIN32)
#include <memory>
#include <type_traits>

#include <DirectXMath.h>

#include <openxr/openxr.h>

#include "xrtl/api.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Loads an OpenXR 2D vector into a DirectX XMVECTOR.
/// </summary>
/// <param name="v">The OpenXR vector to load.</param>
/// <returns>The equivalent XMVECTOR.</returns>
inline DirectX::XMVECTOR load_xmvector(_In_ const XrVector2f& v) noexcept {
    typedef DirectX::XMFLOAT2 xm_type;
    typedef std::decay_t<decltype(v)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");

    auto vv = reinterpret_cast<const xm_type *>(std::addressof(v));
    return DirectX::XMLoadFloat2(vv);
}


/// <summary>
/// Loads an OpenXR 3D vector into a DirectX XMVECTOR.
/// </summary>
/// <param name="v">The OpenXR vector to load.</param>
/// <returns>The equivalent XMVECTOR.</returns>
inline DirectX::XMVECTOR load_xmvector(_In_ const XrVector3f& v) noexcept {
    typedef DirectX::XMFLOAT3 xm_type;
    typedef std::decay_t<decltype(v)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");

    auto vv = reinterpret_cast<const xm_type *>(std::addressof(v));
    return DirectX::XMLoadFloat3(vv);
}


/// <summary>
/// Loads an OpenXR 4D vector into a DirectX XMVECTOR.
/// </summary>
/// <param name="v">The OpenXR vector to load.</param>
/// <returns>The equivalent XMVECTOR.</returns>
inline DirectX::XMVECTOR load_xmvector(_In_ const XrVector4f& v) noexcept {
    typedef DirectX::XMFLOAT4 xm_type;
    typedef std::decay_t<decltype(v)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");

    auto vv = reinterpret_cast<const xm_type *>(std::addressof(v));
    return DirectX::XMLoadFloat4(vv);
}


/// <summary>
/// Loads an OpenXR quaternion into a DirectX XMVECTOR.
/// </summary>
/// <param name="v">The OpenXR quaternion to load.</param>
/// <returns>The equivalent XMVECTOR.</returns>
inline DirectX::XMVECTOR load_xmvector(_In_ const XrQuaternionf& v) noexcept {
    typedef DirectX::XMFLOAT4 xm_type;
    typedef std::decay_t<decltype(v)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");

    auto vv = reinterpret_cast<const xm_type *>(std::addressof(v));
    return DirectX::XMLoadFloat4(vv);
}


/// <summary>
/// Stores a DirectX XMVECTOR into an OpenXR 2D vector.
/// </summary>
/// <param name="d">The OpenXR vector to receive the data.</param>
/// <param name="s">The DirectX vector that is the source of the data.</param>
inline void store_xmvector(_Out_ XrVector2f& d,
        _In_ const DirectX::XMVECTOR s) noexcept {
    typedef DirectX::XMFLOAT2 xm_type;
    typedef std::decay_t<decltype(d)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");
    auto dd = reinterpret_cast<xm_type *>(std::addressof(d));
    DirectX::XMStoreFloat2(dd, s);
}


/// <summary>
/// Stores a DirectX XMVECTOR into an OpenXR 3D vector.
/// </summary>
/// <param name="d">The OpenXR vector to receive the data.</param>
/// <param name="s">The DirectX vector that is the source of the data.</param>
inline void store_xmvector(_Out_ XrVector3f& d,
        _In_ const DirectX::XMVECTOR s) noexcept {
    typedef DirectX::XMFLOAT3 xm_type;
    typedef std::decay_t<decltype(d)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");
    auto dd = reinterpret_cast<xm_type *>(std::addressof(d));
    DirectX::XMStoreFloat3(dd, s);
}


/// <summary>
/// Stores a DirectX XMVECTOR into an OpenXR 4D vector.
/// </summary>
/// <param name="d">The OpenXR vector to receive the data.</param>
/// <param name="s">The DirectX vector that is the source of the data.</param>
inline void store_xmvector(_Out_ XrVector4f& d,
        _In_ const DirectX::XMVECTOR s) noexcept {
    typedef DirectX::XMFLOAT4 xm_type;
    typedef std::decay_t<decltype(d)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");
    auto dd = reinterpret_cast<xm_type *>(std::addressof(d));
    DirectX::XMStoreFloat4(dd, s);
}


/// <summary>
/// Stores a DirectX XMVECTOR into an OpenXR quaternion.
/// </summary>
/// <param name="d">The OpenXR quaternion to receive the data.</param>
/// <param name="s">The DirectX vector that is the source of the data.</param>
inline void store_xmvector(_Out_ XrQuaternionf& d,
        _In_ const DirectX::XMVECTOR s) noexcept {
    typedef DirectX::XMFLOAT4 xm_type;
    typedef std::decay_t<decltype(d)> xr_type;
    static_assert(std::is_trivially_copyable<xr_type>::value, "The OpenXR "
        "type is assume to be a POD type.");
    static_assert(sizeof(xm_type) == sizeof(xr_type), "The OpenXR type is "
        "assumed to have the smae size as the XMath type.");
    auto dd = reinterpret_cast<xm_type *>(std::addressof(d));
    DirectX::XMStoreFloat4(dd, s);
}


/// <summary>
/// Loads an OpenXR pose into a DirectX XMMATRIX.
/// </summary>
/// <param name="p">The pose to be transformed.</param>
/// <returns>The XMMATRIX representing the given pose.</returns>
inline DirectX::XMMATRIX load_xmmatrix(_In_ const XrPosef& p) noexcept {
    auto r = load_xmvector(p.orientation);
    auto t = load_xmvector(p.position);
    auto retval = DirectX::XMMatrixRotationQuaternion(r);
    retval.r[3] = DirectX::XMVectorAdd(retval.r[3], t);
    return retval;
}

XRTL_NAMESPACE_END

#endif /* defined(_WIN32) */

#endif /* !defined(_XRTL_XMATH_H) */
