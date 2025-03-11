// <copyright file="api.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_API_H)
#define _XRTL_API_H
#pragma once


/******************************************************************************\
 * Update the ABI version (i.e. if something in the interface changes) here:  *
\******************************************************************************/
#define XRTL_ABI_MAJOR 0
#define XRTL_ABI_MINOR 1


/// <summary>
/// A helper for implementing <see cref="XRTL_CONCAT" />.
/// </summary>
#define _XRTL_CONCAT(l, r) l ##r


/// <summary>
/// Concatenates two preprocessor symbols.
/// </summary>
/// <param name="l">The left-hand side operand.</param>
/// <param name="r">The right-hand side operand.</param>
#define XRTL_CONCAT(l, r) _XRTL_CONCAT(l, r)


/// <summary>
/// Creates the full ABI versison string.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define XRTL_ABI_VERSION(mj, mn) XRTL_CONCAT(mj, XRTL_CONCAT(_, mn))


/// <summary>
/// Creates the name of the namespace for the specified ABI version.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define XRTL_ABI_NAMESPACE(mj, mn) XRTL_CONCAT(v, XRTL_ABI_VERSION(mj, mn))


/// <summary>
/// Creates the name of the current ABI namespace.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define XRTL_NAMESPACE xrtl::XRTL_ABI_NAMESPACE(XRTL_ABI_MAJOR, XRTL_ABI_MINOR)


/// <summary>
/// Creates the name of the namespace for the implementation details.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define XRTL_DETAIL_NAMESPACE XRTL_NAMESPACE::detail


/// <summary>
/// Marks the begin of the current ABI namespace.
/// </summary>
#define XRTL_NAMESPACE_BEGIN namespace xrtl {\
inline namespace XRTL_ABI_NAMESPACE(XRTL_ABI_MAJOR, XRTL_ABI_MINOR) {

/// <summary>
/// Marks the end of the current ABI namespace.
/// </summary>
#define XRTL_NAMESPACE_END } }

/// <summary>
/// Marks the begin of the namespace for implementation details.
/// </summary>
#define XRTL_DETAIL_NAMESPACE_BEGIN XRTL_NAMESPACE_BEGIN namespace detail {

/// <summary>
/// Marks the end of the namespace for implementation details.
/// </summary>
#define XRTL_DETAIL_NAMESPACE_END } XRTL_NAMESPACE_END


#if defined(_WIN32)
#include <sal.h>

#else /* defined(_WIN32) */
// Empty SAL annotations for rancid platforms.
#define _Analysis_assume_(expr)
#define _In_
#define _Inout_
#define _Inout_opt_
#define _Inout_opt_z_
#define _Inout_updates_(cnt)
#define _In_opt_
#define _In_opt_z_
#define _In_reads_(cnt)
#define _In_reads_bytes_(cnt)
#define _In_reads_or_z_(cnt)
#define _In_z_
#define _Out_
#define _Out_opt_
#define _Out_writes_(cnt)
#define _Out_writes_bytes_(cnt)
#define _Out_writes_opt_(cnt)
#define _Out_writes_opt_z_(cnt)
#define _Ret_
#define _Ret_maybenull_
#define _Ret_maybenull_z_
#define _Ret_null_
#define _Ret_valid_
#define _Ret_z_
#define _When_(expr, annotes)
#endif /* defined(_WIN32) */

#endif /* !defined(_XRTL_API_H) */
