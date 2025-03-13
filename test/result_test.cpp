// <copyright file="result_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace xrtltest {

TEST_CLASS(result_test) {

public:

    TEST_METHOD(test_xr_category) {
        Assert::AreEqual("OpenXR", xrtl::xr_category().name(), L"category name", LINE_INFO());
        Assert::AreEqual(std::string("1"), xrtl::xr_category().message(XR_TIMEOUT_EXPIRED), L"message w/o instance", LINE_INFO());

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
            xrtl::xr_category_instance(instance.get());
            Assert::AreNotEqual(std::string("1"), xrtl::xr_category().message(XR_TIMEOUT_EXPIRED), L"message w/o instance", LINE_INFO());
        }
    }

    TEST_METHOD(test_throw_xr_result) {
        Assert::ExpectException<std::system_error>([](void) {
            THROW_XR_RESULT(XR_TIMEOUT_EXPIRED);
        }, L"THROW_XR_RESULT", LINE_INFO());

        Assert::ExpectException<std::system_error>([](void) {
            THROW_XR_RESULT_MSG(XR_TIMEOUT_EXPIRED, "blah");
        }, L"THROW_XR_RESULT_MSG", LINE_INFO());

        Assert::ExpectException<std::system_error>([](void) {
            THROW_XR_RESULT_IF(XR_TIMEOUT_EXPIRED, true);
        }, L"THROW_XR_RESULT_IF", LINE_INFO());

        Assert::ExpectException<std::system_error>([](void) {
            THROW_XR_RESULT_IF_MSG(XR_TIMEOUT_EXPIRED, true, "blubb");
        }, L"THROW_XR_RESULT_IF_MSG", LINE_INFO());

        Assert::ExpectException<std::system_error>([](void) {
            THROW_IF_XR_FAILED(XR_ERROR_VALIDATION_FAILURE);
        }, L"THROW_XR_THROW_IF_XR_FAILEDRESULT", LINE_INFO());

        Assert::ExpectException<std::system_error>([](void) {
            THROW_IF_XR_FAILED_MSG(XR_ERROR_VALIDATION_FAILURE, "hurz");
        }, L"THROW_IF_XR_FAILED_MSG", LINE_INFO());
    }
};

}
