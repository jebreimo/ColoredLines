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
    program = createProgram();
    auto vertexShader = createShader(GL_VERTEX_SHADER, ColoredLines_vert);
    attachShader(program, vertexShader);
    auto fragmentShader = createShader(GL_FRAGMENT_SHADER, ColoredLines_frag);
    attachShader(program, fragmentShader);
    linkProgram(program);
    useProgram(program);

    positionAttribute = getVertexAttribute(program, "a_Position");
    redOrigin = getUniform<Xyz::Vector2f>(program, "u_RedOrigin");
    redVector = getUniform<Xyz::Vector2f>(program, "u_RedVector");
    redPhase = getUniform<float>(program, "u_RedPhase");
    redPeriod = getUniform<float>(program, "u_RedPeriod");
    greenOrigin = getUniform<Xyz::Vector2f>(program, "u_GreenOrigin");
    greenVector = getUniform<Xyz::Vector2f>(program, "u_GreenVector");
    greenPhase = getUniform<float>(program, "u_GreenPhase");
    greenPeriod = getUniform<float>(program, "u_GreenPeriod");
    blueOrigin = getUniform<Xyz::Vector2f>(program, "u_BlueOrigin");
    blueVector = getUniform<Xyz::Vector2f>(program, "u_BlueVector");
    bluePhase = getUniform<float>(program, "u_BluePhase");
    bluePeriod = getUniform<float>(program, "u_BluePeriod");
}
