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

#ifndef __OPENSPACE_MODULE_VOLUME___ENVELOPE___H__
#define __OPENSPACE_MODULE_VOLUME___ENVELOPE___H__

#include <ghoul/opengl/texture.h>
#include <ghoul/glm.h>
#include <ext/json/json.hpp>
#include <ghoul/lua/ghoul_lua.h>

using json = nlohmann::json;

namespace openspace {
    namespace volume {
        class EnvelopePoint {
        public:
            EnvelopePoint(glm::vec3 c, float x, float y) : color(c), colorHex(getHexadecimalFromVec3(c)), position(std::make_pair(x, y)) {}
            EnvelopePoint(std::string c, float x, float y) : color(hexadecimalToRGBConversion(c)), colorHex(c), position(std::make_pair(x, y)) {}

            int HexadecimalToDecimal(std::string hex) const;
            std::string DecimalToHexadecimal(int dec) const;
            glm::vec3 hexadecimalToRGBConversion(std::string hex) const;
            std::string getHexadecimalFromVec3(glm::vec3 vec) const;

            glm::vec3 color;
            std::string colorHex;
            std::pair<float, float> position;
        };
        class Envelope {
        public:
            Envelope();
            Envelope(std::vector<EnvelopePoint> vec);

            void setPoints(std::vector<EnvelopePoint> vec);
            std::vector<EnvelopePoint> getPoints();

            glm::vec4 getValueAtPosition(float pos) const;
            glm::vec3 normalizeColor(glm::vec3 vec) const;
            json getJSONPoints() const;
            json getJSONEnvelope() const;
            void setEnvelopeLuaTable(lua_State* state) const;

            bool isValueInEnvelope(float pos) const;
            bool isEnvelopeValid() const;

            bool operator!=(const Envelope& env) const;

        private:
           
            std::vector<EnvelopePoint> _points;
        };

    }//namespace volume
}//namespace openspace
#endif __OPENSPACE_MODULE_VOLUME___ENVELOPE___H__
