// <copyright file="traits_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

#include <xrtl/xr_type_traits.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace xrtltest {

TEST_CLASS(traits_test) {

public:

    TEST_METHOD(test_xr_type_traits) {
        Assert::AreEqual(int(XR_TYPE_API_LAYER_PROPERTIES),
            int(xrtl::xr_type_traits<XrApiLayerProperties>::value),
            L"XrApiLayerProperties", LINE_INFO());
        Assert::AreEqual(int(XR_TYPE_EXTENSION_PROPERTIES),
            int(xrtl::xr_type_traits<XrExtensionProperties>::value),
            L"XrExtensionProperties", LINE_INFO());
        Assert::AreEqual(int(XR_TYPE_INSTANCE_CREATE_INFO),
            int(xrtl::xr_type_traits<XrInstanceCreateInfo>::value),
            L"XrInstanceCreateInfo", LINE_INFO());
        Assert::AreEqual(int(XR_TYPE_SYSTEM_GET_INFO),
            int(xrtl::xr_type_traits<XrSystemGetInfo>::value),
            L"XrSystemGetInfo", LINE_INFO());
    }

};

}
