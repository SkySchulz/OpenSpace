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

#include <openspace/properties/vector/uvec3property.h>

#include <ghoul/lua/ghoul_lua.h>
#include <ghoul/glm.h>
#include <ghoul/misc/misc.h>

#include <limits>

namespace {

glm::uvec3 fromLuaConversion(lua_State* state, bool& success) {
    glm::uvec3 result;
    lua_pushnil(state);
    for (glm::length_t i = 0; i < ghoul::glm_components<glm::uvec3>::value; ++i) {
        int hasNext = lua_next(state, -2);
        if (hasNext != 1) {
            success = false;
            return glm::uvec3(0);
        }
        if (lua_isnumber(state, -1) != 1) {
            success = false;
            return glm::uvec3(0);
        }
        else {
            result[i] = static_cast<glm::uvec3::value_type>(lua_tonumber(state, -1));
            lua_pop(state, 1);
        }
    }
    // The last accessor argument and the table are still on the stack
    lua_pop(state, 2);
    success = true;
    return result;
}

bool toLuaConversion(lua_State* state, glm::uvec3 value) {
    lua_newtable(state);
    int number = 1;
    for (glm::length_t i = 0; i < ghoul::glm_components<glm::uvec3>::value; ++i) {
        lua_pushnumber(state, static_cast<lua_Number>(value[i]));
        lua_rawseti(state, -2, number);
        ++number;
    }
    return true;
}

glm::uvec3 fromStringConversion(std::string val, bool& success) {
    glm::uvec3 result;
    std::vector<std::string> tokens = ghoul::tokenizeString(val, ',');
    if (tokens.size() != static_cast<size_t>(result.length())) {
        success = false;
        return result;
    }
    for (glm::length_t i = 0; i < ghoul::glm_components<glm::uvec3>::value; ++i) {
        std::stringstream s(tokens[i]);
        glm::uvec3::value_type v;
        s >> v;
        if (s.fail()) {
            success = false;
            return result;
        }
        else {
            result[i] = v;
        }
    }
    success = true;
    return result;
}

bool toStringConversion(std::string& outValue, glm::uvec3 inValue) {
    outValue = "{";
    for (glm::length_t i = 0; i < ghoul::glm_components<glm::uvec3>::value; ++i) {
        outValue += std::to_string(inValue[i]) + ",";
    }
    outValue.pop_back();
    outValue += "}";
    return true;
}

} // namespace

namespace openspace::properties {

REGISTER_NUMERICALPROPERTY_SOURCE(
    UVec3Property,
    glm::uvec3,
    glm::uvec3(0),
    glm::uvec3(std::numeric_limits<unsigned int>::lowest()),
    glm::uvec3(std::numeric_limits<unsigned int>::max()),
    glm::uvec3(1),
    fromLuaConversion,
    toLuaConversion,
    fromStringConversion,
    toStringConversion,
    LUA_TTABLE
)

} // namespace openspace::properties
