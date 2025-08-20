// <copyright file="debug_policy.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_XRTL_DEBUG_POLICY_H)
#define _XRTL_DEBUG_POLICY_H
#pragma once

#include "xrtl/api.h"


XRTL_NAMESPACE_BEGIN

/// <summary>
/// Configures how the <see cref="debug_messenger"/> behaves.
/// </summary>
enum class debug_policy {

    /// <summary>
    /// The debug messenger is optional, so the library will not fail if it
    /// cannot create the messenger.
    /// </summary>
    optional,

    /// <summary>
    /// The debug messenger is required, so the lubrary will throw if it
    /// cannot load the extension or create the messenger.
    /// </summary>
    required
};

XRTL_NAMESPACE_END

#endif /* !defined(_XRTL_DEBUG_POLICY_H) */
