// <copyright file="maths_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

#include <xrtl/glm.h>
#include <xrtl/matrix.h>
#include <xrtl/xmath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace xrtltest {

TEST_CLASS(maths_test) {

public:

    TEST_METHOD(test_xmath_load_store_vec2) {
        const XrVector2f expected = { 1.0f, 2.0f };

        const auto xm = xrtl::load_xmvector(expected);

        DirectX::XMFLOAT2 xf;
        DirectX::XMStoreFloat2(&xf, xm);
        Assert::AreEqual(expected.x, xf.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xf.y, L"y", LINE_INFO());

        XrVector2f xr;
        xrtl::store_xmvector(xr, xm);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
    }

    TEST_METHOD(test_xmath_load_store_vec3) {
        const XrVector3f expected = { 1.0f, 2.0f, 3.0f };

        const auto xm = xrtl::load_xmvector(expected);

        DirectX::XMFLOAT3 xf;
        DirectX::XMStoreFloat3(&xf, xm);
        Assert::AreEqual(expected.x, xf.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xf.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xf.z, L"z", LINE_INFO());

        XrVector3f xr;
        xrtl::store_xmvector(xr, xm);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xr.z, L"z", LINE_INFO());
    }

    TEST_METHOD(test_xmath_load_store_vec4) {
        const XrVector4f expected = { 1.0f, 2.0f, 3.0f, 4.0f };

        const auto xm = xrtl::load_xmvector(expected);

        DirectX::XMFLOAT4 xf;
        DirectX::XMStoreFloat4(&xf, xm);
        Assert::AreEqual(expected.x, xf.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xf.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xf.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, xf.w, L"w", LINE_INFO());

        XrVector4f xr;
        xrtl::store_xmvector(xr, xm);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xr.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, xr.w, L"w", LINE_INFO());
    }

    TEST_METHOD(test_xmath_load_store_quat) {
        const XrQuaternionf expected = { 1.0f, 2.0f, 3.0f, 4.0f };

        const auto xm = xrtl::load_xmvector(expected);

        DirectX::XMFLOAT4 xf;
        DirectX::XMStoreFloat4(&xf, xm);
        Assert::AreEqual(expected.x, xf.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xf.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xf.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, xf.w, L"w", LINE_INFO());

        XrVector4f xr;
        xrtl::store_xmvector(xr, xm);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xr.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, xr.w, L"w", LINE_INFO());
    }

    TEST_METHOD(test_glm_load_store_vec2) {
        const XrVector2f expected = { 1.0f, 2.0f };

        const auto gl = xrtl::to_glm(expected);
        Assert::AreEqual(expected.x, gl.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, gl.y, L"y", LINE_INFO());

        const auto xr = xrtl::from_glm(gl);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
    }

    TEST_METHOD(test_glm_load_store_vec3) {
        const XrVector3f expected = { 1.0f, 2.0f, 3.0f };

        const auto gl = xrtl::to_glm(expected);
        Assert::AreEqual(expected.x, gl.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, gl.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, gl.z, L"z", LINE_INFO());

        const auto xr = xrtl::from_glm(gl);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xr.z, L"z", LINE_INFO());
    }

    TEST_METHOD(test_glm_load_store_vec4) {
        const XrVector4f expected = { 1.0f, 2.0f, 3.0f, 4.0f };

        const auto gl = xrtl::to_glm(expected);
        Assert::AreEqual(expected.x, gl.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, gl.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, gl.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, gl.w, L"w", LINE_INFO());

        const auto xr = xrtl::from_glm(gl);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xr.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, xr.w, L"w", LINE_INFO());
    }


    TEST_METHOD(test_glm_load_store_quat) {
        const XrQuaternionf expected = { 1.0f, 2.0f, 3.0f, 4.0f };

        const auto gl = xrtl::to_glm(expected);
        Assert::AreEqual(expected.x, gl.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, gl.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, gl.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, gl.w, L"w", LINE_INFO());

        const auto xr = xrtl::from_glm(gl);
        Assert::AreEqual(expected.x, xr.x, L"x", LINE_INFO());
        Assert::AreEqual(expected.y, xr.y, L"y", LINE_INFO());
        Assert::AreEqual(expected.z, xr.z, L"z", LINE_INFO());
        Assert::AreEqual(expected.w, xr.w, L"w", LINE_INFO());
    }

    TEST_METHOD(test_projection) {
        constexpr float near_plane = 0.1f;
        constexpr float far_plane = 100.0f;

        XrFovf fov;
        fov.angleLeft = -0.5f;
        fov.angleRight = 0.5f;
        fov.angleUp = 0.5f;
        fov.angleDown = -0.5f;

        const auto xmm = xrtl::make_matrix(
            DirectX::XMMatrixPerspectiveOffCenterRH,
            fov,
            near_plane,
            far_plane);
        DirectX::XMFLOAT4X4 xm;
        DirectX::XMStoreFloat4x4(&xm, xmm);

        const auto gl = xrtl::make_matrix(
            glm::frustumRH_ZO<float>,
            fov,
            near_plane,
            far_plane);

        Assert::AreEqual(xm._11, gl[0][0], 1e-5f, L"1, 1", LINE_INFO());
        Assert::AreEqual(xm._12, gl[0][1], 1e-5f, L"1, 2", LINE_INFO());
        Assert::AreEqual(xm._13, gl[0][2], 1e-5f, L"1, 3", LINE_INFO());
        Assert::AreEqual(xm._14, gl[0][3], 1e-5f, L"1, 4", LINE_INFO());

        Assert::AreEqual(xm._21, gl[1][0], 1e-5f, L"2, 1", LINE_INFO());
        Assert::AreEqual(xm._22, gl[1][1], 1e-5f, L"2, 2", LINE_INFO());
        Assert::AreEqual(xm._23, gl[1][2], 1e-5f, L"2, 3", LINE_INFO());
        Assert::AreEqual(xm._24, gl[1][3], 1e-5f, L"2, 4", LINE_INFO());

        Assert::AreEqual(xm._31, gl[2][0], 1e-5f, L"3, 1", LINE_INFO());
        Assert::AreEqual(xm._32, gl[2][1], 1e-5f, L"3, 2", LINE_INFO());
        Assert::AreEqual(xm._33, gl[2][2], 1e-5f, L"3, 3", LINE_INFO());
        Assert::AreEqual(xm._34, gl[2][3], 1e-5f, L"3, 4", LINE_INFO());

        Assert::AreEqual(xm._41, gl[3][0], 1e-5f, L"4, 1", LINE_INFO());
        Assert::AreEqual(xm._42, gl[3][1], 1e-5f, L"4, 2", LINE_INFO());
        Assert::AreEqual(xm._43, gl[3][2], 1e-5f, L"4, 3", LINE_INFO());
        Assert::AreEqual(xm._44, gl[3][3], 1e-5f, L"4, 4", LINE_INFO());
    }

    TEST_METHOD(test_pose) {
        XrPosef pose;
        pose.position.x = 1.0f;
        pose.position.y = 0.0f;
        pose.position.z = 0.0f;
        pose.orientation.x = 0.0f;
        pose.orientation.y = 0.5f * ::sqrt(2.0f);
        pose.orientation.z = 0.0f;
        pose.orientation.w = pose.orientation.y;

        const auto xmm = xrtl::load_xmmatrix(pose);
        DirectX::XMFLOAT4X4 xm;
        DirectX::XMStoreFloat4x4(&xm, xmm);

        const auto gl = xrtl::to_glm(pose);

        Assert::AreEqual(xm._11, gl[0][0], 1e-5f, L"1, 1", LINE_INFO());
        Assert::AreEqual(xm._12, gl[0][1], 1e-5f, L"1, 2", LINE_INFO());
        Assert::AreEqual(xm._13, gl[0][2], 1e-5f, L"1, 3", LINE_INFO());
        Assert::AreEqual(xm._14, gl[0][3], 1e-5f, L"1, 4", LINE_INFO());

        Assert::AreEqual(xm._21, gl[1][0], 1e-5f, L"2, 1", LINE_INFO());
        Assert::AreEqual(xm._22, gl[1][1], 1e-5f, L"2, 2", LINE_INFO());
        Assert::AreEqual(xm._23, gl[1][2], 1e-5f, L"2, 3", LINE_INFO());
        Assert::AreEqual(xm._24, gl[1][3], 1e-5f, L"2, 4", LINE_INFO());

        Assert::AreEqual(xm._31, gl[2][0], 1e-5f, L"3, 1", LINE_INFO());
        Assert::AreEqual(xm._32, gl[2][1], 1e-5f, L"3, 2", LINE_INFO());
        Assert::AreEqual(xm._33, gl[2][2], 1e-5f, L"3, 3", LINE_INFO());
        Assert::AreEqual(xm._34, gl[2][3], 1e-5f, L"3, 4", LINE_INFO());

        Assert::AreEqual(xm._41, gl[3][0], 1e-5f, L"4, 1", LINE_INFO());
        Assert::AreEqual(xm._42, gl[3][1], 1e-5f, L"4, 2", LINE_INFO());
        Assert::AreEqual(xm._43, gl[3][2], 1e-5f, L"4, 3", LINE_INFO());
        Assert::AreEqual(xm._44, gl[3][3], 1e-5f, L"4, 4", LINE_INFO());
    }
};

}
