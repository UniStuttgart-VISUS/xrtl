// <copyright file="init_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace xrtltest {

TEST_CLASS(init_test) {

public:

    TEST_METHOD(test_inplace_initialise) {
        XrActionSetCreateInfo info;
        xrtl::initialise_xrstruct(info);
        Assert::AreEqual(int(XR_TYPE_ACTION_SET_CREATE_INFO), int(info.type), L"type", LINE_INFO());
    }

    TEST_METHOD(test_initialise) {
        auto info = xrtl::initialise_xrstruct<XrActionSetCreateInfo>();
        Assert::AreEqual(int(XR_TYPE_ACTION_SET_CREATE_INFO), int(info.type), L"type", LINE_INFO());
    }
};

}
