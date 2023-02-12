//****************************************************************************
// Copyright © 2021 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2021-09-21.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <Tungsten/SdlApplication.hpp>
#include "ColoredLinesShaderProgram.hpp"

class ColoredLines : public Tungsten::EventLoop
{
public:
    void on_startup(Tungsten::SdlApplication& app) final
    {
        app.set_swap_interval(1);
        m_VertexArray = Tungsten::generate_vertex_array();
        Tungsten::bind_vertex_array(m_VertexArray);

        m_Buffers = Tungsten::generate_buffers(2);
        float square[] = {-1.0f, -1.0f, 0.0f,
                          1.0f, -1.0f, 0.0f,
                          1.0f, 1.0f, 0.0f,
                          -1.0f, 1.0f, 0.0f};
        short indexes[] = {0, 2, 3, 0, 1, 2};

        Tungsten::bind_buffer(GL_ARRAY_BUFFER, m_Buffers[0]);
        Tungsten::set_buffer_data(GL_ARRAY_BUFFER, sizeof(square),
                                square, GL_STATIC_DRAW);
        Tungsten::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[1]);
        Tungsten::set_buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes),
                                indexes, GL_STATIC_DRAW);
        m_ElementCount = std::size(indexes);

        m_Program.setup();
        Tungsten::define_vertex_attribute_pointer(m_Program.positionAttribute, 3,
                                               GL_FLOAT, false, 0, 0);
        Tungsten::enable_vertex_attribute(m_Program.positionAttribute);
    }

    [[nodiscard]]
    static std::pair<Xyz::Vector2F, Xyz::Vector2F>
    get_point(float width, float height, float angle)
    {
        auto center = Xyz::make_vector2(width * 0.5f, height * 0.5f);
        auto radius = Xyz::get_length(center);
        auto direction = Xyz::make_vector2(cos(angle), sin(angle));
        return {center + radius * direction, direction};
    }

    void on_draw(Tungsten::SdlApplication& app) final
    {
        constexpr float PI = Xyz::Constants<float>::PI;
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto [w, h] = app.window_size();
        auto blueAngle = 2 * PI * float(SDL_GetTicks() % 20000) / 20000.0f;
        auto [blueOrigin, blueDirection] = get_point(float(w), float(h), blueAngle);
        m_Program.bluePhase.set(2 * PI * float(SDL_GetTicks() % 500) / 500.0f);
        m_Program.bluePeriod.set(0.08f + 0.04f * sin(2 * PI * float(SDL_GetTicks() % 7000) / 7000.0f));
        m_Program.blueVector.set(blueDirection);
        m_Program.blueOrigin.set(blueOrigin);
        auto greenAngle = 2 * PI * float(SDL_GetTicks() % 37000) / 37000.0f;
        auto[greenOrigin, greenDirection] = get_point(float(w), float(h), greenAngle);
        m_Program.greenPhase.set(2 * PI * float(SDL_GetTicks() % 700) / 700.0f);
        m_Program.greenPeriod.set(0.06f + 0.03f * sin(2 * PI * float(SDL_GetTicks() % 13000) / 13000.0f));
        m_Program.greenVector.set(greenDirection);
        m_Program.greenOrigin.set(greenOrigin);
        auto redAngle = 2 * PI * float(SDL_GetTicks() % 53000) / 53000.0f;
        auto[redOrigin, redDirection] = get_point(float(w), float(h), redAngle);
        m_Program.redPhase.set(2 * PI * float(SDL_GetTicks() % 300) / 300.0f);
        m_Program.redPeriod.set(0.07f + 0.05f * sin(2 * PI * float(SDL_GetTicks() % 19000) / 19000.0f));
        m_Program.redVector.set(redDirection);
        m_Program.redOrigin.set(redOrigin);
        Tungsten::draw_elements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_SHORT);
        redraw();
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
        app.parse_command_line_options(argc, argv);
        app.run();
    }
    catch (Tungsten::TungstenException& ex)
    {
        std::cerr << ex.what() << "\n";
        return 1;
    }
    return 0;
}
