// <copyright file="unique_handle_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

#include <xrtl/unique_handle.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace xrtltest {

TEST_CLASS(unique_handle_test) {

public:

    TEST_METHOD(test_instance) {
        XrInstanceCreateInfo ci { XR_TYPE_INSTANCE_CREATE_INFO };
        ::strncpy_s(ci.applicationInfo.applicationName, "Test", XR_MAX_APPLICATION_NAME_SIZE);
        ci.applicationInfo.applicationVersion = 1;
        ::strncpy_s(ci.applicationInfo.engineName, "Test", XR_MAX_ENGINE_NAME_SIZE);
        ci.applicationInfo.engineVersion = 1;
        ci.applicationInfo.apiVersion = XR_MAKE_VERSION(1, 0, 0);
        ci.enabledApiLayerCount = 0;
        ci.enabledExtensionCount = 0;

        xrtl::unique_instance instance;
        Assert::AreEqual(0, int(::xrCreateInstance(&ci, instance.put())), L"Create instance", LINE_INFO());
    }
};

}
