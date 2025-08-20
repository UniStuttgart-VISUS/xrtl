// <copyright file="debug_messenger.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * XRTL_NAMESPACE::debug_messenger<Policy>::debug_messenger
 */
template<XRTL_NAMESPACE::debug_policy Policy>
XRTL_NAMESPACE::debug_messenger<Policy>::debug_messenger(
        _In_ XrInstance instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info)
    : _destroy(nullptr),
        _handle(XR_NULL_HANDLE) {
    this->create(instance, create_info);
}


/*
 * XRTL_NAMESPACE::debug_messenger<Policy>::debug_messenger
 */
template<XRTL_NAMESPACE::debug_policy Policy>
template<class TCallback>
XRTL_NAMESPACE::debug_messenger<Policy>::debug_messenger(
        _In_ XrInstance instance,
        _In_ const TCallback &callback,
        _In_ const XrDebugUtilsMessageSeverityFlagsEXT severities,
        _In_ const XrDebugUtilsMessageTypeFlagsEXT types,
        _In_ void *context)
    : _destroy(nullptr),
        _handle(XR_NULL_HANDLE) {
    auto create_info = init_xrstruct<XrDebugUtilsMessengerCreateInfoEXT>();
    create_info.messageTypes = types;
    create_info.messageSeverities = severities;
    create_info.userCallback = callback;
    create_info.userData = context;
    this->create(instance, create_info);
}


/*
 * XRTL_NAMESPACE::debug_messenger<Policy>::~debug_messenger
 */
template<XRTL_NAMESPACE::debug_policy Policy>
XRTL_NAMESPACE::debug_messenger<Policy>::~debug_messenger(void) noexcept {
    if ((this->_destroy != nullptr) && (this->_handle != XR_NULL_HANDLE)) {
        this->_destroy(this->_handle);
    }
}


/*
 * XRTL_NAMESPACE::debug_messenger<Policy>::create
 */
template<XRTL_NAMESPACE::debug_policy Policy>
void XRTL_NAMESPACE::debug_messenger<Policy>::create(_In_ XrInstance instance,
        _In_ const XrDebugUtilsMessengerCreateInfoEXT& create_info) {
    assert(this->_handle == XR_NULL_HANDLE);
    assert(instance != XR_NULL_HANDLE);

    if ((instance == XR_NULL_HANDLE) && (Policy == debug_policy::required)) {
        throw std::invalid_argument("A valid OpenXR instance is required.");
    }

    if (instance != XR_NULL_HANDLE) {
        auto create = this->load(instance);
        if (create != nullptr) {
            assert(this->_destroy != XR_NULL_HANDLE);
            auto status = create(instance, &create_info, &this->_handle);
            THROW_XR_RESULT_IF_MSG(status,
                XR_FAILED(status) && (Policy == debug_policy::required),
                "Failed to create debug messenger.");
        }
    }
}


/*
 * XRTL_NAMESPACE::debug_messenger<Policy>::load
 */
template<XRTL_NAMESPACE::debug_policy Policy>
PFN_xrCreateDebugUtilsMessengerEXT XRTL_NAMESPACE::debug_messenger<Policy>::load(
        _In_ XrInstance instance) {
    assert(instance != XR_NULL_HANDLE);
    assert(this->_destroy == nullptr);

    {
        auto status = ::xrGetInstanceProcAddr(instance,
            "xrDestroyDebugUtilsMessengerEXT",
            reinterpret_cast<PFN_xrVoidFunction *>(&this->_destroy));
        if (XR_FAILED(status)) {
            THROW_XR_RESULT_IF_MSG(status, Policy == debug_policy::required,
                "Failed to obtain address of xrDestroyDebugUtilsMessengerEXT");
            return nullptr;
        }
    }

    {
        PFN_xrCreateDebugUtilsMessengerEXT retval;
        auto status = ::xrGetInstanceProcAddr(instance,
            "xrCreateDebugUtilsMessengerEXT",
            reinterpret_cast<PFN_xrVoidFunction *>(&retval));
        if (XR_FAILED(status)) {
            THROW_XR_RESULT_IF_MSG(status, Policy == debug_policy::required,
                "Failed to obtain address of xrCreateDebugUtilsMessengerEXT");
            return nullptr;
        }

        return retval;
    }
}
