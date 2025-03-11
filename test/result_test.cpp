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
        xrtl::unique_instance instance;
        Assert::AreEqual(0, int(::xrCreateInstance(&ci, instance.put())), L"Create instance", LINE_INFO());

        xrtl::xr_category_instance(instance.get());
        Assert::AreNotEqual(std::string("1"), xrtl::xr_category().message(XR_TIMEOUT_EXPIRED), L"message w/o instance", LINE_INFO());
    }

    TEST_METHOD(test_throw_xr_result) {
        Assert::ExpectException<std::system_error>([](void) {
            THROW_XR_RESULT(XR_TIMEOUT_EXPIRED);
        }, L"THROW_XR_RESULT", LINE_INFO());

        Assert::ExpectException<std::system_error>([](void) {
            THROW_XR_RESULT_MSG(XR_TIMEOUT_EXPIRED, "blah");
        }, L"THROW_XR_RESULT_MSG", LINE_INFO());
    }
};

}
