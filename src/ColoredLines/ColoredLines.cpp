//****************************************************************************
// Copyright © 2021 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2021-09-21.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <Tungsten/Shapes.hpp>
#include <Tungsten/SdlApplication.hpp>
#include "ColoredLinesShaderProgram.hpp"

class ColoredLines : public Tungsten::EventLoop
{
public:
    void onStartup(Tungsten::SdlApplication& app) final
    {
        app.setSwapInterval(1);
        m_VertexArray = Tungsten::generateVertexArray();
        Tungsten::bindVertexArray(m_VertexArray);

        m_Buffers = Tungsten::generateBuffers(2);
        Tungsten::ArrayBufferBuilder builder(3);
        Tungsten::addRectangle(builder, Xyz::Rectangle<float>({-1, -1}, {2, 2}));
        setBuffers(m_Buffers[0], m_Buffers[1], builder);
        m_ElementCount = builder.elementCount();

        m_Program.setup();
        Tungsten::defineVertexAttributePointer(m_Program.positionAttribute, 3,
                                               GL_FLOAT, false, 0, 0);
        Tungsten::enableVertexAttribute(m_Program.positionAttribute);
    }

    std::pair<Xyz::Vector2f, Xyz::Vector2f>
    getPoint(float width, float height, float angle)
    {
        auto center = Xyz::makeVector2(width * 0.5f, height * 0.5f);
        auto radius = Xyz::getLength(center);
        auto direction = Xyz::makeVector2(cos(angle), sin(angle));
        return {center + radius * direction, direction};
    }

    void onDraw(Tungsten::SdlApplication& app) final
    {
        constexpr float PI = Xyz::Constants<float>::PI;
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto [w, h] = app.windowSize();
        auto blueAngle = 2 * PI * float(SDL_GetTicks() % 20000) / 20000.0f;
        auto [blueOrigin, blueDirection] = getPoint(float(w), float(h), blueAngle);
        m_Program.bluePhase.set(2 * PI * float(SDL_GetTicks() % 500) / 500.0f);
        m_Program.bluePeriod.set(0.08f + 0.04f * sin(2 * PI * float(SDL_GetTicks() % 7000) / 7000.0f));
        m_Program.blueVector.set(blueDirection);
        m_Program.blueOrigin.set(blueOrigin);
        auto greenAngle = 2 * PI * float(SDL_GetTicks() % 37000) / 37000.0f;
        auto[greenOrigin, greenDirection] = getPoint(float(w), float(h), greenAngle);
        m_Program.greenPhase.set(2 * PI * float(SDL_GetTicks() % 700) / 700.0f);
        m_Program.greenPeriod.set(0.06f + 0.03f * sin(2 * PI * float(SDL_GetTicks() % 13000) / 13000.0f));
        m_Program.greenVector.set(greenDirection);
        m_Program.greenOrigin.set(greenOrigin);
        auto redAngle = 2 * PI * float(SDL_GetTicks() % 53000) / 53000.0f;
        auto[redOrigin, redDirection] = getPoint(float(w), float(h), redAngle);
        m_Program.redPhase.set(2 * PI * float(SDL_GetTicks() % 300) / 300.0f);
        m_Program.redPeriod.set(0.07f + 0.05f * sin(2 * PI * float(SDL_GetTicks() % 19000) / 19000.0f));
        m_Program.redVector.set(redDirection);
        m_Program.redOrigin.set(redOrigin);
        Tungsten::drawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_SHORT);
    }
private:
    std::vector<Tungsten::BufferHandle> m_Buffers;
    Tungsten::VertexArrayHandle m_VertexArray;
    ColoredLinesShaderProgram m_Program;
    GLsizei m_ElementCount = 0;
};

int main(int argc, char* argv[])
{
    Tungsten::SdlApplication app("ColoredLines", std::make_unique<ColoredLines>());
    try
    {
        app.parseCommandLineOptions(argc, argv);
        app.run();
    }
    catch (Tungsten::TungstenException& ex)
    {
        std::cerr << ex.what() << "\n";
        return 1;
    }
    return 0;
}
