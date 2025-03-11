// <copyright file="unique_handle.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * XRTL_NAMESPACE::unique_handle<THandle, TDelete>::reset
 */
template<class THandle, XrResult(*TDelete)(THandle)>
void XRTL_NAMESPACE::unique_handle<THandle, TDelete>::reset(
        _In_opt_ handle_type handle) noexcept {
    if (*this) {
        TDelete(this->_handle);
    }

    this->_handle = handle;
}


/*
 * XRTL_NAMESPACE::unique_handle<THandle, TDelete>::operator =
 */
template<class THandle, XrResult(*TDelete)(THandle)>
XRTL_NAMESPACE::unique_handle<THandle, TDelete>&
XRTL_NAMESPACE::unique_handle<THandle, TDelete>::operator =(
        _Inout_ unique_handle&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = XR_NULL_HANDLE;
    }

    return *this;
}
