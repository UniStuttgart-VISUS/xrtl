// <copyright file="path_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

#include <xrtl/path.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace xrtltest {

TEST_CLASS(path_test) {

public:

    TEST_METHOD(test_dft_ctor) {
        xrtl::path p;
        Assert::IsFalse(p, L"Not valid", LINE_INFO());
        Assert::IsTrue(p.empty(), L"Empty", LINE_INFO());
    }

    TEST_METHOD(test_parse_ctor) {
        XrInstanceCreateInfo ci { XR_TYPE_INSTANCE_CREATE_INFO };
        ::strncpy_s(ci.applicationInfo.applicationName, "Test", XR_MAX_APPLICATION_NAME_SIZE);
        ci.applicationInfo.applicationVersion = 1;
        ::strncpy_s(ci.applicationInfo.engineName, "Test", XR_MAX_ENGINE_NAME_SIZE);
        ci.applicationInfo.engineVersion = 1;
        ci.applicationInfo.apiVersion = XR_MAKE_VERSION(1, 0, 0);
        ci.enabledApiLayerCount = 0;
        ci.enabledExtensionCount = 0;
        xrtl::unique_instance instance;

        if (XR_SUCCEEDED(::xrCreateInstance(&ci, instance.put()))) {
            const auto expected = "/interaction_profiles/ext/eye_gaze_interaction";
            xrtl::path p(instance, expected);
            Assert::IsTrue(p, L"Valid", LINE_INFO());
            Assert::IsFalse(p.empty(), L"Not empty", LINE_INFO());
            Assert::AreEqual(expected, p.to_string(instance).c_str(), L"String representation", LINE_INFO());
        }
    }

};

}
