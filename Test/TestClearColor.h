//
// Created by 13191 on 2025/11/28.
//

#ifndef LEARNINGPROJECT03_TESTCLEARCOLOR_H
#define LEARNINGPROJECT03_TESTCLEARCOLOR_H
#include "Test.h"

namespace test
{
    class TestClearColor : public Test
    {
        public:
        TestClearColor();
        ~TestClearColor() override;

        void OnRender() override;
        void OnUpdate(float deltaTime) override;
        void OnImGuiRender() override;
    private:
        float m_ClearColor[4];
    };
} // test

#endif //LEARNINGPROJECT03_TESTCLEARCOLOR_H