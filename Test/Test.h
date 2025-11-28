//
// Created by 13191 on 2025/11/28.
//

#ifndef LEARNINGPROJECT03_TEST_H
#define LEARNINGPROJECT03_TEST_H

namespace test
{
    class Test
    {
    public:
        Test(){};
        virtual ~Test(){};

        virtual void OnUpdate(float deltaTime)
        {
        }

        virtual void OnRender()
        {
        }

        virtual void OnImGuiRender()
        {
        }
    };
} // test

#endif //LEARNINGPROJECT03_TEST_H
