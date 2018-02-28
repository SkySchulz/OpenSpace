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

#include "fragment.glsl"
#include "floatoperations.glsl"

// Keep in sync with renderablegaiastars.h:ColumnOption enum
const int COLUMNOPTION_STATIC = 0;
const int COLUMNOPTION_MOTION = 1; 
const int COLUMNOPTION_COLOR = 2;

in vec4 vs_position;
in vec3 ge_velocity;
in float ge_brightness;
in vec4 ge_gPosition;
in vec2 texCoord;
in float ge_observationDistance;

uniform sampler2D psfTexture;
uniform sampler1D colorTexture;
uniform float magnitudeExponent;
uniform float sharpness;
uniform int columnOption;

vec4 mag2rgb(float magnitude) {
    // DR1 mag is [4, 20]
    float st = (magnitude - 4) / (20 - 4);
    return texture(colorTexture, st);
}

Fragment getFragment() {

    vec4 color = vec4(1.0);

    if ( columnOption == COLUMNOPTION_COLOR ) {
        color = mag2rgb(ge_brightness);
    }

    vec4 textureColor = texture(psfTexture, texCoord);
    vec4 fullColor = vec4(color.rgb, textureColor.a);
    fullColor.a = pow(fullColor.a, sharpness);

    float d = magnitudeExponent - log(ge_observationDistance) / log(10.0);
    fullColor.a *= clamp(d, 0.0, 1.0);

    if (fullColor.a == 0) {
        discard;
    }

    Fragment frag;
    frag.color = fullColor;
    frag.depth = safeLength(vs_position);
    frag.gPosition = ge_gPosition;
    frag.gNormal = vec4(0.0, 0.0, 0.0, 1.0);

    return frag;
}
