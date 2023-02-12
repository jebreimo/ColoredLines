//****************************************************************************
// Copyright © 2021 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2021-09-21.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include "ColoredLinesShaderProgram.hpp"
#include "ColoredLines-frag.glsl.hpp"
#include "ColoredLines-vert.glsl.hpp"

void ColoredLinesShaderProgram::setup()
{
    using namespace Tungsten;
    program = create_program();
    auto vertexShader = create_shader(GL_VERTEX_SHADER, ColoredLines_vert);
    attach_shader(program, vertexShader);
    auto fragmentShader = create_shader(GL_FRAGMENT_SHADER, ColoredLines_frag);
    attach_shader(program, fragmentShader);
    link_program(program);
    use_program(program);

    positionAttribute = get_vertex_attribute(program, "a_Position");
    redOrigin = get_uniform<Xyz::Vector2F>(program, "u_RedOrigin");
    redVector = get_uniform<Xyz::Vector2F>(program, "u_RedVector");
    redPhase = get_uniform<float>(program, "u_RedPhase");
    redPeriod = get_uniform<float>(program, "u_RedPeriod");
    greenOrigin = get_uniform<Xyz::Vector2F>(program, "u_GreenOrigin");
    greenVector = get_uniform<Xyz::Vector2F>(program, "u_GreenVector");
    greenPhase = get_uniform<float>(program, "u_GreenPhase");
    greenPeriod = get_uniform<float>(program, "u_GreenPeriod");
    blueOrigin = get_uniform<Xyz::Vector2F>(program, "u_BlueOrigin");
    blueVector = get_uniform<Xyz::Vector2F>(program, "u_BlueVector");
    bluePhase = get_uniform<float>(program, "u_BluePhase");
    bluePeriod = get_uniform<float>(program, "u_BluePeriod");
}
