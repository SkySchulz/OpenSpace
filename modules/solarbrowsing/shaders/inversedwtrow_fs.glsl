

/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2017                                                               *
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

uniform sampler2DRect compressedImageryTexture;
uniform sampler2DRect filterTex;
uniform sampler2DRect lut;
uniform float level;
uniform float levelTest;

in vec4 vs_positionScreenSpace;
in vec2 vs_st;
layout(location = 0) out vec4 color;

Fragment getFragment() {

    float lookup, level_center = level + 0.5;
    vec2 st, filter_st;
    vec3 sum = vec3(0);

    // Look up alpha (lut.g) and beta (lut.b)
    lookup = texture(lut, vec2(vs_st.x * 4096.0, level_center)).g;
    filter_st = vec2(lookup*9.0 + 0.5, 0.5); // 0 - low-pass, 1 - high-pass
    st = vec2(0.0, vs_st.y * 4096.0 );

    // Look up indirect address (lut.r) & filter values (filter.x) then convolve
    for (int i = 0; i < 9; i++) {
      st.x = texture(lut, vec2(vs_st.x * 4096.0 + i, level_center)).r;
      // Convolve corresponding filter values with data from level j
      sum += texture(filterTex, filter_st).xyz * texture(compressedImageryTexture, st).xyz;
      filter_st.x += 1.0;
    }
    //vec4 diffuse = texture(compressedImageryTexture, vs_st * 4096.0); //vec4(sum, 1.0);
    //vec4 diffuse = vec4(levelTest, levelTest, levelTest, 1.0);
    vec4 diffuse = vec4(sum, 1.0);
    //vec4 diffuse = vec4(0.5, 0.5, 1.0, 1.0);

    Fragment frag;
    frag.color = diffuse;
    frag.depth = 1.0;
    return frag;
}
