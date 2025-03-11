// <copyright file="unique_handle_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace xrtltest {

TEST_CLASS(unique_handle_test) {

public:

    TEST_METHOD(test_instance) {
        XrInstanceCreateInfo ci { XR_TYPE_INSTANCE_CREATE_INFO };
        xrtl::unique_instance instance;
        Assert::AreEqual(0, int(::xrCreateInstance(&ci, instance.put())), L"Create instance", LINE_INFO());
    }
};

}
