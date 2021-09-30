//****************************************************************************
// Copyright © 2021 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2021-09-21.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#version 100

uniform highp vec2 u_RedOrigin;
uniform highp vec2 u_RedVector;
uniform highp float u_RedPhase;
uniform highp float u_RedPeriod;
uniform highp vec2 u_GreenOrigin;
uniform highp vec2 u_GreenVector;
uniform highp float u_GreenPhase;
uniform highp float u_GreenPeriod;
uniform highp vec2 u_BlueOrigin;
uniform highp vec2 u_BlueVector;
uniform highp float u_BluePhase;
uniform highp float u_BluePeriod;

void main()
{
    highp float tmpRed = dot(u_RedVector, (gl_FragCoord.xy - u_RedOrigin));
    highp float red = u_RedPhase + u_RedPeriod * tmpRed;
    highp float tmpGreen = dot(u_GreenVector, (gl_FragCoord.xy - u_GreenOrigin));
    highp float green = u_GreenPhase + u_GreenPeriod * tmpGreen;
    highp float tmpBlue = dot(u_BlueVector, (gl_FragCoord.xy - u_BlueOrigin));
    highp float blue = u_BluePhase + u_BluePeriod * tmpBlue;
    gl_FragColor = vec4(0.5 + 0.5 * sin(red), 0.5 + 0.5 * sin(green), 0.5 + 0.5 * sin(blue), 1.0);
}
