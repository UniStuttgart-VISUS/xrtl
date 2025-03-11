// <copyright file="xr_error_category.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * XRTL_DETAIL_NAMESPACE::xr_error_category<TError>::default_error_condition
 */
template<class TError>
std::error_condition
XRTL_DETAIL_NAMESPACE::xr_error_category<TError>::default_error_condition(
        _In_ const int error) const noexcept {
    return std::error_condition(error, xrtl::xr_category());
}


/*
 * XRTL_DETAIL_NAMESPACE::xr_error_category<TError>::message
 */
template<class TError>
std::string XRTL_DETAIL_NAMESPACE::xr_error_category<TError>::message(
        _In_ const int error) const {
    if (this->_instance == nullptr) {
        return std::to_string(error);

    } else {
        static char retval[XR_MAX_RESULT_STRING_SIZE];
        auto result = static_cast<value_type>(error);
        ::xrResultToString(this->_instance, result, retval);
        return retval;
    }
}


/*
 * XRTL_DETAIL_NAMESPACE::xr_error_category<TError>::name
 */
template<class TError>
_Ret_z_ const char *XRTL_DETAIL_NAMESPACE::xr_error_category<TError>::name(
        void) const noexcept {
    return "OpenXR";
}


/*
 * XRTL_NAMESPACE::xr_category_instance
 */
inline void XRTL_NAMESPACE::xr_category_instance(_In_opt_ XrInstance instance) {
    typedef detail::xr_error_category<XrResult> category;
    detail::xr_category<category>()._instance = instance;
}
