/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2018                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#version __CONTEXT__

#include "PowerScaling/powerScaling_vs.hglsl"

in vec4 in_position;
in vec3 in_brightness;
in vec3 in_velocity;
in float in_speed;

out vec3 vs_brightness;
out vec3 vs_velocity;
out float vs_speed;
out vec4 vs_correctedPositionViewSpace;

uniform mat4 modelCameraMatrix;
uniform mat4 viewMatrix;

void main() {
    vs_brightness = in_brightness;
    vs_velocity   = in_velocity;
    vs_speed      = in_speed;

    vec4 positionCameraRigSpace = modelCameraMatrix * in_position;

    vs_correctedPositionViewSpace = viewMatrix * (vec4(1E19, 1E19, 1E19, 1.0) * positionCameraRigSpace);
    
    gl_Position = positionCameraRigSpace;
}
