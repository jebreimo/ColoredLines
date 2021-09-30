//****************************************************************************
// Copyright © 2021 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2021-09-21.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once
#include "Tungsten/Tungsten.hpp"

class ColoredLinesShaderProgram
{
public:
    void setup();

    Tungsten::ProgramHandle program;
    Tungsten::Uniform<Xyz::Vector2f> redOrigin;
    Tungsten::Uniform<Xyz::Vector2f> redVector;
    Tungsten::Uniform<float> redPhase;
    Tungsten::Uniform<float> redPeriod;
    Tungsten::Uniform<Xyz::Vector2f> greenOrigin;
    Tungsten::Uniform<Xyz::Vector2f> greenVector;
    Tungsten::Uniform<float> greenPhase;
    Tungsten::Uniform<float> greenPeriod;
    Tungsten::Uniform<Xyz::Vector2f> blueOrigin;
    Tungsten::Uniform<Xyz::Vector2f> blueVector;
    Tungsten::Uniform<float> bluePhase;
    Tungsten::Uniform<float> bluePeriod;
    GLuint positionAttribute;
};
