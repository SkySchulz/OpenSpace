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

#include <modules/digitaluniverse/rendering/renderableplanescloud.h>

#include <openspace/documentation/documentation.h>
#include <openspace/documentation/verifier.h>
#include <openspace/util/updatestructures.h>
#include <openspace/engine/openspaceengine.h>
#include <openspace/rendering/renderengine.h>

#include <ghoul/filesystem/filesystem.h>
#include <ghoul/misc/templatefactory.h>
#include <ghoul/io/texture/texturereader.h>
#include <ghoul/opengl/programobject.h>
#include <ghoul/opengl/texture.h>
#include <ghoul/opengl/textureunit.h>
#include <ghoul/font/fontmanager.h>
#include <ghoul/font/fontrenderer.h>

#include <glm/gtx/string_cast.hpp>
#include <ghoul/glm.h>

#include <array>
#include <fstream>
#include <stdint.h>
#include <locale>
#include <string>

namespace {
    constexpr const char* _loggerCat        = "RenderablePlanesCloud";
    constexpr const char* KeyFile           = "File";
    constexpr const char* keyUnit           = "Unit";
    constexpr const char* MeterUnit         = "m";
    constexpr const char* KilometerUnit     = "Km";
    constexpr const char* ParsecUnit        = "pc";
    constexpr const char* KiloparsecUnit    = "Kpc";
    constexpr const char* MegaparsecUnit    = "Mpc";
    constexpr const char* GigaparsecUnit    = "Gpc";
    constexpr const char* GigalightyearUnit = "Gly";

    constexpr int8_t CurrentCacheVersion = 2;
    constexpr float PARSEC = 0.308567756E17f;

    enum BlendMode {
        BlendModeNormal = 0,
        BlendModeAdditive
    };

    static const openspace::properties::Property::PropertyInfo TransparencyInfo = {
        "Transparency",
        "Transparency",
        "This value is a multiplicative factor that is applied to the transparency of "
        "all points."
    };

    static const openspace::properties::Property::PropertyInfo ScaleFactorInfo = {
        "ScaleFactor",
        "Scale Factor",
        "This value is used as a multiplicative factor that is applied to the apparent "
        "size of each point."
    };

    static const openspace::properties::Property::PropertyInfo TextColorInfo = {
        "TextColor",
        "Text Color",
        "The text color for the astronomical object."
    };

    static const openspace::properties::Property::PropertyInfo TextSizeInfo = {
        "TextSize",
        "Text Size",
        "The text size for the astronomical object labels."
    };

    static const openspace::properties::Property::PropertyInfo LabelFileInfo = {
        "LabelFile",
        "Label File",
        "The path to the label file that contains information about the astronomical "
        "objects being rendered."
    };

    static const openspace::properties::Property::PropertyInfo LabelMinSizeInfo = {
        "TextMinSize",
        "Text Min Size",
        "The minimal size (in pixels) of the text for the labels for the astronomical "
        "objects being rendered."
    };

    static const openspace::properties::Property::PropertyInfo LabelMaxSizeInfo = {
        "TextMaxSize",
        "Text Max Size",
        "The maximum size (in pixels) of the text for the labels for the astronomical "
        "objects being rendered."
    };

    static const openspace::properties::Property::PropertyInfo DrawElementsInfo = {
        "DrawElements",
        "Draw Elements",
        "Enables/Disables the drawing of the astronomical objects."
    };

    static const openspace::properties::Property::PropertyInfo TransformationMatrixInfo =
    {
        "TransformationMatrix",
        "Transformation Matrix",
        "Transformation matrix to be applied to each astronomical object."
    };

    static const openspace::properties::Property::PropertyInfo BlendModeInfo = {
        "BlendMode",
        "Blending Mode",
        "This determines the blending mode that is applied to this plane."
    };

    static const openspace::properties::Property::PropertyInfo TexturePathInfo = {
        "TexturePath",
        "Texture Path",
        "This value specifies the path for the textures in disk."
    };

    static const openspace::properties::Property::PropertyInfo LuminosityInfo = {
        "Luminosity",
        "Luminosity variable",
        "Datavar variable to control the luminosity/size of the astronomical objects."
    };

    static const openspace::properties::Property::PropertyInfo ScaleLuminosityInfo = {
        "ScaleLuminosity",
        "ScaleLuminosity variable",
        "Scaling control for the luminosity/size of the astronomical objects."
    };

    static const openspace::properties::Property::PropertyInfo RenderOptionInfo = {
        "RenderOptionInfo",
        "Render Option",
        "Debug option for rendering of billboards and texts."
    };

    static const openspace::properties::Property::PropertyInfo FadeInDistancesInfo = {
        "FadeInDistances",
        "Fade-In Start and End Distances",
        "These values determine the initial and final distances from the center of "
        "our galaxy from which the astronomical object will start and end "
        "fading-in."
    };

    static const openspace::properties::Property::PropertyInfo DisableFadeInInfo = {
        "DisableFadeIn",
        "Disable Fade-in effect",
        "Enables/Disables the Fade-in effect."
    };

    static const openspace::properties::Property::PropertyInfo PlaneMinSizeInfo = {
        "PlaneMinSize",
        "Plane Min Size in Pixels",
        "The min size (in pixels) for the plane representing the astronomical "
        "object."
    };

}  // namespace

namespace openspace {

documentation::Documentation RenderablePlanesCloud::Documentation() {
    using namespace documentation;
    return {
        "RenderablePlanesCloud",
        "digitaluniverse_RenderablePlanesCloud",
        {
            {
                "Type",
                new StringEqualVerifier("RenderablePlanesCloud"),
                Optional::No
            },
            {
                KeyFile,
                new StringVerifier,
                Optional::Yes,
                "The path to the SPECK file that contains information about the "
                "astronomical object being rendered."
            },
            {
                TransparencyInfo.identifier,
                new DoubleVerifier,
                Optional::No,
                TransparencyInfo.description
            },
            {
                ScaleFactorInfo.identifier,
                new DoubleVerifier,
                Optional::Yes,
                ScaleFactorInfo.description
            },
            {
                TextColorInfo.identifier,
                new DoubleVector4Verifier,
                Optional::Yes,
                TextColorInfo.description
            },
            {
                TextSizeInfo.identifier,
                new DoubleVerifier,
                Optional::Yes,
                TextSizeInfo.description
            },
            {
                LabelFileInfo.identifier,
                new StringVerifier,
                Optional::Yes,
                LabelFileInfo.description
            },
            {
                LabelMinSizeInfo.identifier,
                new IntVerifier,
                Optional::Yes,
                LabelMinSizeInfo.description
            },
            {
                LabelMaxSizeInfo.identifier,
                new IntVerifier,
                Optional::Yes,
                LabelMaxSizeInfo.description
            },
            {
                TransformationMatrixInfo.identifier,
                new Matrix4x4Verifier<double>,
                Optional::Yes,
                TransformationMatrixInfo.description
            },
            {
                BlendModeInfo.identifier,
                new StringInListVerifier({ "Normal", "Additive" }),
                Optional::Yes,
                BlendModeInfo.description, // + " The default value is 'Normal'.",
            },
            {
                TexturePathInfo.identifier,
                new StringVerifier,
                Optional::No,
                TexturePathInfo.description,
            },
            {
                LuminosityInfo.identifier,
                new StringVerifier,
                Optional::Yes,
                LuminosityInfo.description,
            },
            {
                ScaleFactorInfo.identifier,
                new DoubleVerifier,
                Optional::Yes,
                ScaleFactorInfo.description,
            },
            {
                FadeInDistancesInfo.identifier,
                new Vector2Verifier<float>,
                Optional::Yes,
                FadeInDistancesInfo.description
            },
            {
                DisableFadeInInfo.identifier,
                new BoolVerifier,
                Optional::Yes,
                DisableFadeInInfo.description
            },
            {
                PlaneMinSizeInfo.identifier,
                new DoubleVerifier,
                Optional::Yes,
                PlaneMinSizeInfo.description
            },
        }
    };
}


RenderablePlanesCloud::RenderablePlanesCloud(const ghoul::Dictionary& dictionary)
    : Renderable(dictionary)
    , _hasSpeckFile(false)
    , _dataIsDirty(true)
    , _textColorIsDirty(true)
    , _hasLabel(false)
    , _labelDataIsDirty(true)
    , _textMinSize(0)
    , _textMaxSize(200)
    , _planeStartingIndexPos(0)
    , _textureVariableIndex(0)
    , _alphaValue(TransparencyInfo, 1.f, 0.f, 1.f)
    , _scaleFactor(ScaleFactorInfo, 1.f, 0.f, 50.f)
    , _textColor(
        TextColorInfo,
        glm::vec4(1.0f, 1.0, 1.0f, 1.f),
        glm::vec4(0.f),
        glm::vec4(1.f)
    )
    , _textSize(TextSizeInfo, 8.0, 0.5, 24.0)
    , _drawElements(DrawElementsInfo, true)
    , _blendMode(BlendModeInfo, properties::OptionProperty::DisplayType::Dropdown)
    , _fadeInDistance(
        FadeInDistancesInfo,
        glm::vec2(0.f),
        glm::vec2(0.f),
        glm::vec2(200000.f)
    )
    , _disableFadeInDistance(DisableFadeInInfo, true)
    , _planeMinSize(PlaneMinSizeInfo, 0.5, 0.0, 500.0)
    , _renderOption(RenderOptionInfo, properties::OptionProperty::DisplayType::Dropdown)
    , _program(nullptr)
    , _font(nullptr)
    , _speckFile("")
    , _labelFile("")
    , _texturesPath("")
    , _luminosityVar("")
    , _unit(Parsec)
    , _nValuesPerAstronomicalObject(0)
    , _sluminosity(1.f)
    , _transformationMatrix(glm::dmat4(1.0))
{
    documentation::testSpecificationAndThrow(
        Documentation(),
        dictionary,
        "RenderablePlanesCloud"
    );

    if (dictionary.hasKey(KeyFile)) {
        _speckFile = absPath(dictionary.value<std::string>(KeyFile));
        _hasSpeckFile = true;
        _drawElements.onChange([&]() {
            _hasSpeckFile = _hasSpeckFile == true? false : true; });
        addProperty(_drawElements);
    }

    // DEBUG:
    _renderOption.addOption(0, "Camera View Direction");
    _renderOption.addOption(1, "Camera Position Normal");
    _renderOption.addOption(2, "Screen center Position Normal");
    addProperty(_renderOption);
    //_renderOption.set(1);

    if (dictionary.hasKey(keyUnit)) {
        std::string unit = dictionary.value<std::string>(keyUnit);
        if (unit == MeterUnit) {
            _unit = Meter;
        }
        else if (unit == KilometerUnit) {
            _unit = Kilometer;
        }
        else if (unit == ParsecUnit) {
            _unit = Parsec;
        }
        else if (unit == KiloparsecUnit) {
            _unit = Kiloparsec;
        }
        else if (unit == MegaparsecUnit) {
            _unit = Megaparsec;
        }
        else if (unit == GigaparsecUnit) {
            _unit = Gigaparsec;
        }
        else if (unit == GigalightyearUnit) {
            _unit = GigalightYears;
        }
        else {
            LWARNING("No unit given for RenderablePlanesCloud. Using meters as units.");
            _unit = Meter;
        }
    }
    else {
        LWARNING("No unit given for RenderablePlanesCloud. Using meters as units.");
        _unit = Meter;
    }

    if (dictionary.hasKey(TransparencyInfo.identifier)) {
        _alphaValue = static_cast<float>(
            dictionary.value<double>(TransparencyInfo.identifier)
        );
    }
    addProperty(_alphaValue);

    if (dictionary.hasKey(ScaleFactorInfo.identifier)) {
        _scaleFactor = static_cast<float>(
            dictionary.value<double>(ScaleFactorInfo.identifier)
        );
    }
    addProperty(_scaleFactor);
    _scaleFactor.onChange([&]() {
        _dataIsDirty = true;
    });

    if (dictionary.hasKey(LabelFileInfo.identifier)) {
        _labelFile = absPath(dictionary.value<std::string>(
            LabelFileInfo.identifier
        ));
        _hasLabel = true;

        if (dictionary.hasKey(TextColorInfo.identifier)) {
            _textColor = dictionary.value<glm::vec4>(TextColorInfo.identifier);
            _hasLabel = true;
        }
        _textColor.setViewOption(properties::Property::ViewOptions::Color);
        addProperty(_textColor);
        _textColor.onChange([&]() { _textColorIsDirty = true; });


        if (dictionary.hasKey(TextSizeInfo.identifier)) {
            _textSize = dictionary.value<float>(TextSizeInfo.identifier);
        }
        addProperty(_textSize);

        if (dictionary.hasKey(LabelMinSizeInfo.identifier)) {
            _textMinSize = static_cast<int>(
                dictionary.value<float>(LabelMinSizeInfo.identifier)
            );
        }

        if (dictionary.hasKey(LabelMaxSizeInfo.identifier)) {
            _textMaxSize = static_cast<int>(
                dictionary.value<float>(LabelMaxSizeInfo.identifier)
            );
        }
    }

    if (dictionary.hasKey(TransformationMatrixInfo.identifier)) {
        _transformationMatrix = dictionary.value<glm::dmat4>(
            TransformationMatrixInfo.identifier
        );
    }

    _blendMode.addOptions({
        { BlendModeNormal, "Normal" },
        { BlendModeAdditive, "Additive" }
    });
    _blendMode.onChange([&]() {
        switch (_blendMode) {
        case BlendModeNormal:
            setRenderBin(Renderable::RenderBin::Opaque);
            break;
        case BlendModeAdditive:
            setRenderBin(Renderable::RenderBin::Transparent);
            break;
        default:
            throw ghoul::MissingCaseException();
        }
    });

    if (dictionary.hasKey(BlendModeInfo.identifier)) {
        const std::string v = dictionary.value<std::string>(BlendModeInfo.identifier);
        if (v == "Normal") {
            _blendMode = BlendModeNormal;
        }
        else if (v == "Additive") {
            _blendMode = BlendModeAdditive;
        }
    }

    _texturesPath = absPath(dictionary.value<std::string>(TexturePathInfo.identifier));

    if (dictionary.hasKey(LuminosityInfo.identifier)) {
        _luminosityVar = dictionary.value<std::string>(LuminosityInfo.identifier);
    }

    if (dictionary.hasKey(ScaleLuminosityInfo.identifier)) {
        _sluminosity = static_cast<float>(
            dictionary.value<double>(ScaleLuminosityInfo.identifier)
        );
    }

    if (dictionary.hasKey(FadeInDistancesInfo.identifier)) {
        glm::vec2 fadeInValue = dictionary.value<glm::vec2>(
            FadeInDistancesInfo.identifier
        );
        _fadeInDistance.set(fadeInValue);
        _disableFadeInDistance.set(false);
        addProperty(_fadeInDistance);
        addProperty(_disableFadeInDistance);
    }

    if (dictionary.hasKey(PlaneMinSizeInfo.identifier)) {
        _planeMinSize = static_cast<float>(
            dictionary.value<double>(PlaneMinSizeInfo.identifier)
        );
        addProperty(_planeMinSize);
    }
}

bool RenderablePlanesCloud::isReady() const {
    return ((_program != nullptr) && (!_fullData.empty())) || (!_labelData.empty());
}

void RenderablePlanesCloud::initialize() {
    bool success = loadData();
    if (!success) {
        throw ghoul::RuntimeError("Error loading data");
    }
}

void RenderablePlanesCloud::initializeGL() {
    RenderEngine& renderEngine = OsEng.renderEngine();

    _program = renderEngine.buildRenderProgram(
        "RenderablePlanesCloud",
        absPath("${MODULE_DIGITALUNIVERSE}/shaders/plane_vs.glsl"),
        absPath("${MODULE_DIGITALUNIVERSE}/shaders/plane_fs.glsl")
    );

    _uniformCache.modelViewProjectionTransform = _program->uniformLocation(
        "modelViewProjectionTransform"
    );
    _uniformCache.alphaValue = _program->uniformLocation("alphaValue");
    _uniformCache.fadeInValue = _program->uniformLocation("fadeInValue");
    _uniformCache.galaxyTexture = _program->uniformLocation("galaxyTexture");

    createPlanes();

    loadTextures();

    if (_hasLabel) {
        if (_font == nullptr) {
            size_t _fontSize = 30;
            _font = OsEng.fontManager().font(
                "Mono",
                static_cast<float>(_fontSize),
                ghoul::fontrendering::FontManager::Outline::Yes,
                ghoul::fontrendering::FontManager::LoadGlyphs::No
            );
        }
    }
}


void RenderablePlanesCloud::deleteDataGPU() {
    for (RenderingPlane& renderingPlane : _renderingPlanesArray) {
        glDeleteVertexArrays(1, &renderingPlane.vao);
        glDeleteBuffers(1, &renderingPlane.vbo);
    }
}

void RenderablePlanesCloud::deinitializeGL() {
    deleteDataGPU();

    RenderEngine& renderEngine = OsEng.renderEngine();
    if (_program) {
        renderEngine.removeRenderProgram(_program);
        _program = nullptr;
    }
}

void RenderablePlanesCloud::renderPlanes(const RenderData&,
                                         const glm::dmat4& modelViewMatrix,
                                         const glm::dmat4& projectionMatrix,
                                         const float fadeInVariable)
{
    // Saving current OpenGL state
    GLboolean blendEnabled = glIsEnabledi(GL_BLEND, 0);
    GLenum blendEquationRGB;
    GLenum blendEquationAlpha;
    GLenum blendDestAlpha;
    GLenum blendDestRGB;
    GLenum blendSrcAlpha;
    GLenum blendSrcRGB;

    glGetIntegerv(GL_BLEND_EQUATION_RGB, &blendEquationRGB);
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &blendEquationAlpha);
    glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDestAlpha);
    glGetIntegerv(GL_BLEND_DST_RGB, &blendDestRGB);
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrcAlpha);
    glGetIntegerv(GL_BLEND_SRC_RGB, &blendSrcRGB);

    glEnablei(GL_BLEND, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(false);

    _program->activate();

    glm::dmat4 modelViewProjectionMatrix = glm::dmat4(projectionMatrix) * modelViewMatrix;
    _program->setUniform(
        _uniformCache.modelViewProjectionTransform,
        modelViewProjectionMatrix
    );
    _program->setUniform(_uniformCache.alphaValue, _alphaValue);
    _program->setUniform(_uniformCache.fadeInValue, fadeInVariable);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    ghoul::opengl::TextureUnit unit;
    unit.activate();
    _program->setUniform(_uniformCache.galaxyTexture, unit);
    int currentTextureIndex = -1;
    for (const RenderingPlane& renderingPlane : _renderingPlanesArray) {
        // For planes with undefined textures references
        if (renderingPlane.planeIndex == -1) {
            continue;
        }

        glm::dvec4 vertex0(renderingPlane.vertexData[0], renderingPlane.vertexData[1],
            renderingPlane.vertexData[2], renderingPlane.vertexData[3]);
        glm::dvec4 vertex1(renderingPlane.vertexData[6], renderingPlane.vertexData[7],
            renderingPlane.vertexData[8], renderingPlane.vertexData[9]);

        vertex0 = modelViewProjectionMatrix * vertex0;
        vertex1 = modelViewProjectionMatrix * vertex1;

        // Testing size:
        glm::vec4 topRight = vertex1 / vertex1.w;
        topRight = ((topRight + glm::vec4(1.0)) / glm::vec4(2.0)) *
                   glm::vec4(viewport[2], viewport[3], 1.0, 1.0);
        glm::vec4 bottomLeft = vertex0 / vertex0.w;
        bottomLeft = ((bottomLeft + glm::vec4(1.0)) / glm::vec4(2.0)) *
                   glm::vec4(viewport[2], viewport[3], 1.0, 1.0);

        float lengthY  = std::fabs(topRight.y - bottomLeft.y);
        float lengthX  = std::fabs(topRight.x - bottomLeft.x);
        float lengthXY = glm::length(glm::vec2(topRight) - glm::vec2(bottomLeft));
        float biggestAxis =
            lengthY > lengthX ? (lengthY > lengthXY ? lengthY : lengthXY) :
            (lengthX > lengthXY ? lengthX : lengthXY);
        if (biggestAxis < _planeMinSize ) {
            continue;
        }

        if (currentTextureIndex != renderingPlane.planeIndex) {
            _textureMap[renderingPlane.planeIndex]->bind();
            currentTextureIndex = renderingPlane.planeIndex;
        }
        glBindVertexArray(renderingPlane.vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    //if (additiveBlending) {
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    //glDepthMask(true);
    //}

    glBindVertexArray(0);
    _program->deactivate();

    // Restores blending state
    glBlendEquationSeparate(blendEquationRGB, blendEquationAlpha);
    glBlendFuncSeparate(blendSrcRGB, blendDestRGB, blendSrcAlpha, blendDestAlpha);

    glDepthMask(true);

    if (!blendEnabled) {
        glDisablei(GL_BLEND, 0);
    }
}

void RenderablePlanesCloud::renderLabels(const RenderData& data,
                                         const glm::dmat4& modelViewProjectionMatrix,
                                         const glm::dvec3& orthoRight,
                                         const glm::dvec3& orthoUp, float fadeInVariable)
{
    float scale = 0.0;
    switch (_unit) {
        case Meter:
            scale = 1.0;
            break;
        case Kilometer:
            scale = 1e3;
            break;
        case Parsec:
            scale = PARSEC;
            break;
        case Kiloparsec:
            scale = 1e3 * PARSEC;
            break;
        case Megaparsec:
            scale = 1e6 * PARSEC;
            break;
        case Gigaparsec:
            scale = 1e9 * PARSEC;
            break;
        case GigalightYears:
            scale = 306391534.73091 * PARSEC;
            break;
    }

    glm::vec4 textColor = _textColor;
    textColor.a *= fadeInVariable;
    for (const std::pair<glm::vec3, std::string>& pair : _labelData) {
        //glm::vec3 scaledPos(_transformationMatrix * glm::dvec4(pair.first, 1.0));
        glm::vec3 scaledPos(pair.first);
        scaledPos *= scale;
        ghoul::fontrendering::FontRenderer::defaultProjectionRenderer().render(
            *_font,
            scaledPos,
            //_textColor,
            textColor,
            pow(10.0, _textSize.value()),
            _textMinSize,
            _textMaxSize,
            modelViewProjectionMatrix,
            orthoRight,
            orthoUp,
            data.camera.positionVec3(),
            data.camera.lookUpVectorWorldSpace(),
            _renderOption.value(),
            "%s",
            pair.second.c_str());
    }
}

void RenderablePlanesCloud::render(const RenderData& data, RendererTasks&) {
    double scale = 0.0;
    switch (_unit) {
        case Meter:
            scale = 1.0;
            break;
        case Kilometer:
            scale = 1e3;
            break;
        case Parsec:
            scale = PARSEC;
            break;
        case Kiloparsec:
            scale = 1e3 * PARSEC;
            break;
        case Megaparsec:
            scale = 1e6 * PARSEC;
            break;
        case Gigaparsec:
            scale = 1e9 * PARSEC;
            break;
        case GigalightYears:
            scale = 306391534.73091 * PARSEC;
            break;
    }

    float fadeInVariable = 1.0f;
    if (!_disableFadeInDistance) {
        double distCamera = glm::length(data.camera.positionVec3());
        //float funcValue = static_cast<float>(
            //(1.0 / double(_fadeInDistance))*(distCamera / scale)
        //);
        //
        //// Let's not waste performance
        //if (funcValue < 0.01) {
        //    return;
        //}

        //fadeInVariable = funcValue > 1.0 ? 1.0 : funcValue;

        glm::vec2 fadeRange = _fadeInDistance;
        float a = 1.0f / ((fadeRange.y - fadeRange.x) * scale);
        float b = -(fadeRange.x / (fadeRange.y - fadeRange.x));
        float funcValue = a * distCamera + b;
        fadeInVariable *= funcValue > 1.0 ? 1.0 : funcValue;

        if (funcValue < 0.01) {
            return;
        }
    }

    glm::dmat4 modelMatrix =
        glm::translate(glm::dmat4(1.0), data.modelTransform.translation) * // Translation
        glm::dmat4(data.modelTransform.rotation) *  // Spice rotation
        glm::scale(glm::dmat4(1.0), glm::dvec3(data.modelTransform.scale));

    glm::dmat4 modelViewMatrix = data.camera.combinedViewMatrix() * modelMatrix;
    glm::mat4 projectionMatrix = data.camera.projectionMatrix();
    glm::dmat4 modelViewProjectionMatrix = glm::dmat4(projectionMatrix) * modelViewMatrix;

    //glm::vec3 lookup = data.camera.lookUpVectorWorldSpace();
    //glm::vec3 viewDirection = data.camera.viewDirectionWorldSpace();
    //glm::vec3 right = glm::cross(viewDirection, lookup);
    //glm::vec3 up = glm::cross(right, viewDirection);

    //glm::dmat4 worldToModelTransform = glm::inverse(modelMatrix);
    //glm::vec3 orthoRight = glm::normalize(
    //    glm::vec3(worldToModelTransform * glm::vec4(right, 0.0))
    //);
    //glm::vec3 orthoUp = glm::normalize(
    //    glm::vec3(worldToModelTransform * glm::vec4(up, 0.0))
    //);

    //glm::dmat4 invMVP = glm::inverse(modelViewProjectionMatrix);
    glm::dmat4 invMVPParts = glm::inverse(modelMatrix) *
                             glm::inverse(data.camera.combinedViewMatrix()) *
                             glm::inverse(glm::dmat4(projectionMatrix));
    glm::dvec3 orthoRight = glm::dvec3(
        glm::normalize(glm::dvec3(invMVPParts * glm::dvec4(1.0, 0.0, 0.0, 0.0)))
    );
    glm::dvec3 orthoUp = glm::dvec3(
        glm::normalize(glm::dvec3(invMVPParts * glm::dvec4(0.0, 1.0, 0.0, 0.0)))
    );

    if (_hasSpeckFile) {
        renderPlanes(data, modelViewMatrix, projectionMatrix, fadeInVariable);
    }

    if (_hasLabel) {
        renderLabels(
            data,
            modelViewProjectionMatrix,
            orthoRight,
            orthoUp,
            fadeInVariable
        );
    }
}

void RenderablePlanesCloud::update(const UpdateData&) {
    if (_dataIsDirty  && _hasSpeckFile) {
        deleteDataGPU();
        createPlanes();
        _dataIsDirty = false;
    }

    if (_program->isDirty()) {
        _program->rebuildFromFile();

        _uniformCache.modelViewProjectionTransform = _program->uniformLocation(
            "modelViewProjectionTransform"
        );
        _uniformCache.alphaValue = _program->uniformLocation("alphaValue");
        _uniformCache.fadeInValue = _program->uniformLocation("fadeInValue");
        _uniformCache.galaxyTexture = _program->uniformLocation("galaxyTexture");
    }
}

bool RenderablePlanesCloud::loadData() {
    bool success = false;
    if (_hasSpeckFile) {
        std::string _file = _speckFile;
        // I disabled the cache as it didn't work on Mac --- abock
        // std::string cachedFile = FileSys.cacheManager()->cachedFilename(
        //     _file,
        //     ghoul::filesystem::CacheManager::Persistent::Yes
        // );

        // bool hasCachedFile = FileSys.fileExists(cachedFile);
        // if (hasCachedFile) {
        //     LINFO(
        //         "Cached file '" << cachedFile <<
        //         "' used for Speck file '" << _file << "'"
        //     );

        //     success = loadCachedFile(cachedFile);
        //     if (!success) {
        //         FileSys.cacheManager()->removeCacheFile(_file);
        //         // Intentional fall-through to the 'else' to generate the cache
        //         // file for the next run
        //     }
        // }
        // else
        // {
        //     LINFO("Cache for Speck file '" << _file << "' not found");
        LINFO(fmt::format("Loading Speck file '{}'", _file));

            success = readSpeckFile();
            if (!success) {
                return false;
            }

            // LINFO("Saving cache");
            //success &= saveCachedFile(cachedFile);
        // }
    }

    std::string labelFile = _labelFile;
    if (!labelFile.empty()) {
        // I disabled the cache as it didn't work on Mac --- abock
        // std::string cachedFile = FileSys.cacheManager()->cachedFilename(
        //     labelFile,
        //     ghoul::filesystem::CacheManager::Persistent::Yes
        // );
        // bool hasCachedFile = FileSys.fileExists(cachedFile);
        // if (hasCachedFile) {
        //     LINFO(
        //         "Cached file '" << cachedFile <<
        //         "' used for Label file '" << labelFile << "'"
        //     );
        //
        //     success &= loadCachedFile(cachedFile);
        //     if (!success) {
        //         FileSys.cacheManager()->removeCacheFile(labelFile);
        //         // Intentional fall-through to the 'else' to generate the cache
        //         // file for the next run
        //     }
        // }
        // else
        // {
        //     LINFO("Cache for Label file '" << labelFile << "' not found");
            LINFO(fmt::format("Loading Label file '{}'", labelFile));

            success &= readLabelFile();
            if (!success) {
                return false;
            }

        // }
    }

    return success;
}

bool RenderablePlanesCloud::loadTextures() {
    if (!_textureFileMap.empty()) {
        for (auto pair : _textureFileMap) {
            auto p = _textureMap.insert(std::make_pair(
                pair.first,
                ghoul::io::TextureReader::ref().loadTexture(pair.second)
            ));
            if (p.second) {
                LINFOC(
                    "RenderablePlanesCloud",
                    fmt::format("Loaded texture from '{}'", pair.second)
                );
                auto it = p.first;
                it->second->uploadTexture();
                it->second->setFilter(ghoul::opengl::Texture::FilterMode::LinearMipMap);
            }
        }
    }
    else {
        return false;
    }
    return true;
}

bool RenderablePlanesCloud::readSpeckFile() {
    std::string _file = _speckFile;
    std::ifstream file(_file);
    if (!file.good()) {
        LERROR(fmt::format("Failed to open Speck file '{}'", _file));
        return false;
    }

    _nValuesPerAstronomicalObject = 0;

    // The beginning of the speck file has a header that either contains comments
    // (signaled by a preceding '#') or information about the structure of the file
    // (signaled by the keywords 'datavar', 'texturevar', and 'texture')
    std::string line = "";
    while (true) {
        std::streampos position = file.tellg();
        std::getline(file, line);

        // Guard against wrong line endings (copying files from Windows to Mac) causes
        // lines to have a final \r
        if (!line.empty() && line.back() == '\r') {
            line = line.substr(0, line.length() -1);
        }

        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (line.substr(0, 7) != "datavar" &&
            line.substr(0, 10) != "texturevar" &&
            line.substr(0, 7) != "texture" &&
            line.substr(0, 10) != "polyorivar" &&
            line.substr(0, 10) != "maxcomment")
        {
            // we read a line that doesn't belong to the header, so we have to jump back
            // before the beginning of the current line
            file.seekg(position);
            break;
        }

        if (line.substr(0, 7) == "datavar") {
            // datavar lines are structured as follows:
            // datavar # description
            // where # is the index of the data variable; so if we repeatedly overwrite
            // the 'nValues' variable with the latest index, we will end up with the total
            // number of values (+3 since X Y Z are not counted in the Speck file index)
            std::stringstream str(line);

            std::string dummy;
            str >> dummy; // command
            str >> _nValuesPerAstronomicalObject; // variable index
            dummy.clear();
            str >> dummy; // variable name

            // +3 because of the x, y and z at the begining of each line.
            _variableDataPositionMap.insert({ dummy, _nValuesPerAstronomicalObject + 3});

            if ((dummy == "orientation") || (dummy == "ori")) { // 3d vectors u and v
                // We want the number, but the index is 0 based
                _nValuesPerAstronomicalObject += 6;
            }
            else {
                // We want the number, but the index is 0 based
                _nValuesPerAstronomicalObject += 1;
            }
        }

        if (line.substr(0, 10) == "polyorivar") {
            _planeStartingIndexPos = 0;
            std::stringstream str(line);

            std::string dummy;
            str >> dummy; // command
            str >> _planeStartingIndexPos;
            _planeStartingIndexPos += 3; // 3 for xyz
        }

        if (line.substr(0, 10) == "texturevar") {
            _textureVariableIndex = 0;
            std::stringstream str(line);

            std::string dummy;
            str >> dummy; // command
            str >> _textureVariableIndex;
            _textureVariableIndex += 3; // 3 for xyz
        }

        if (line.substr(0, 8) == "texture ") {
            std::stringstream str(line);

            std::size_t found = line.find("-");

            int textureIndex = 0;

            std::string dummy;
            str >> dummy; // command

            if (found != std::string::npos) {
                std::string option; // Not being used right now.
                str >> option;
            }

            str >> textureIndex;
            str >> dummy; // texture file name

            _textureFileMap.insert(
            {textureIndex, absPath(_texturesPath + "/" + dummy) }
            );
        }
    }

    _nValuesPerAstronomicalObject += 3; // X Y Z are not counted in the Speck file indices

    do {
        std::vector<float> values(_nValuesPerAstronomicalObject);

        std::getline(file, line);

        // Guard against wrong line endings (copying files from Windows to Mac) causes
        // lines to have a final \r
        if (!line.empty() && line.back() == '\r') {
            line = line.substr(0, line.length() -1);
        }

        if (line.empty()) {
            continue;
        }

        std::stringstream str(line);

        glm::vec3 u(0.0f), v(0.0f);
        int textureIndex = 0;

        for (int i = 0; i < _nValuesPerAstronomicalObject; ++i) {
            str >> values[i];
            if ((i >= _planeStartingIndexPos) &&
                (i <= _planeStartingIndexPos + 6)) { // vectors u and v
                int index = i - _planeStartingIndexPos;
                switch (index) {
                case 0:
                    u.x = values[i];
                    break;
                case 1:
                    u.y = values[i];
                    break;
                case 2:
                    u.z = values[i];
                    break;
                case 3:
                    v.x = values[i];
                    break;
                case 4:
                    v.y = values[i];
                    break;
                case 5:
                    v.z = values[i];
                    break;
                }
            }

            // JCC: This should be moved to the RenderablePlanesCloud:
            if (i == _textureVariableIndex) {
                textureIndex = static_cast<int>(values[i]);
            }
        }
        _fullData.insert(_fullData.end(), values.begin(), values.end());
    } while (!file.eof());

    return true;
}

bool RenderablePlanesCloud::readLabelFile() {
    std::string _file = _labelFile;
    std::ifstream file(_file);
    if (!file.good()) {
        LERROR(fmt::format("Failed to open Label file '{}'", _file));
        return false;
    }

    // The beginning of the speck file has a header that either contains comments
    // (signaled by a preceding '#') or information about the structure of the file
    // (signaled by the keywords 'datavar', 'texturevar', and 'texture')
    std::string line = "";
    while (true) {
        std::streampos position = file.tellg();
        std::getline(file, line);

        // Guard against wrong line endings (copying files from Windows to Mac) causes
        // lines to have a final \r
        if (!line.empty() && line.back() == '\r') {
            line = line.substr(0, line.length() -1);
        }

        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (line.substr(0, 9) != "textcolor") {
            // we read a line that doesn't belong to the header, so we have to jump back
            // before the beginning of the current line
            file.seekg(position);
            continue;
        }

        if (line.substr(0, 9) == "textcolor") {
            // textcolor lines are structured as follows:
            // textcolor # description
            // where # is color text defined in configuration file
            std::stringstream str(line);

            // TODO: handle cases of labels with different colors
            break;
        }
    }

    do {
        std::vector<float> values(_nValuesPerAstronomicalObject);

        std::getline(file, line);

        // Guard against wrong line endings (copying files from Windows to Mac) causes
        // lines to have a final \r
        if (!line.empty() && line.back() == '\r') {
            line = line.substr(0, line.length() -1);
        }

        if (line.empty()) {
            continue;
        }

        std::stringstream str(line);

        glm::vec3 position;
        for (auto j = 0; j < 3; ++j) {
            str >> position[j];
        }

        std::string dummy;
        str >> dummy; // text keyword

        std::string label;
        str >> label;
        dummy.clear();

        while (str >> dummy) {
            label += " " + dummy;
            dummy.clear();
        }

        glm::vec3 transformedPos = glm::vec3(
            _transformationMatrix * glm::dvec4(position, 1.0)
        );
        _labelData.push_back(std::make_pair(transformedPos, label));

    } while (!file.eof());

    return true;
}

bool RenderablePlanesCloud::loadCachedFile(const std::string& file) {
    std::ifstream fileStream(file, std::ifstream::binary);
    if (fileStream.good()) {
        int8_t version = 0;
        fileStream.read(reinterpret_cast<char*>(&version), sizeof(int8_t));
        if (version != CurrentCacheVersion) {
            LINFO("The format of the cached file has changed: deleting old cache");
            fileStream.close();
            FileSys.deleteFile(file);
            return false;
        }

        int32_t nValues = 0;
        fileStream.read(reinterpret_cast<char*>(&nValues), sizeof(int32_t));
        fileStream.read(reinterpret_cast<char*>(
            &_nValuesPerAstronomicalObject),
            sizeof(int32_t)
        );

        _fullData.resize(nValues);
        fileStream.read(reinterpret_cast<char*>(&_fullData[0]),
            nValues * sizeof(_fullData[0]));

        bool success = fileStream.good();
        return success;
    }
    else {
        LERROR(fmt::format("Error opening file '{}' for loading cache file", file));
        return false;
    }
}

bool RenderablePlanesCloud::saveCachedFile(const std::string& file) const {
    std::ofstream fileStream(file, std::ofstream::binary);
    if (fileStream.good()) {
        fileStream.write(reinterpret_cast<const char*>(&CurrentCacheVersion),
            sizeof(int8_t));

        int32_t nValues = static_cast<int32_t>(_fullData.size());
        if (nValues == 0) {
            LERROR("Error writing cache: No values were loaded");
            return false;
        }
        fileStream.write(reinterpret_cast<const char*>(&nValues), sizeof(int32_t));

        int32_t nValuesPerAstronomicalObject = static_cast<int32_t>(
            _nValuesPerAstronomicalObject
        );
        fileStream.write(reinterpret_cast<const char*>(
            &nValuesPerAstronomicalObject),
            sizeof(int32_t)
        );

        size_t nBytes = nValues * sizeof(_fullData[0]);
        fileStream.write(reinterpret_cast<const char*>(&_fullData[0]), nBytes);

        bool success = fileStream.good();
        return success;
    }
    else {
        LERROR(fmt::format("Error opening file '{}' for save cache file", file));
        return false;
    }
}

void RenderablePlanesCloud::createPlanes() {
    if (_dataIsDirty && _hasSpeckFile) {
        LDEBUG("Creating planes");
        float maxSize = 0.0f;
        for (size_t p = 0; p < _fullData.size(); p += _nValuesPerAstronomicalObject) {
            glm::vec4 transformedPos = glm::vec4(_transformationMatrix *
                glm::dvec4(_fullData[p + 0], _fullData[p + 1], _fullData[p + 2], 1.0));

            // Plane vectors u and v
            glm::vec4 u = glm::vec4(_transformationMatrix *
                glm::dvec4(
                    _fullData[p + _planeStartingIndexPos + 0],
                    _fullData[p + _planeStartingIndexPos + 1],
                    _fullData[p + _planeStartingIndexPos + 2],
                    1.0));
            u /= 2.f;
            u.w = 0.0;
            glm::vec4 v = glm::vec4(_transformationMatrix *
                glm::dvec4(
                    _fullData[p + _planeStartingIndexPos + 3],
                    _fullData[p + _planeStartingIndexPos + 4],
                    _fullData[p + _planeStartingIndexPos + 5],
                    1.0));
            v /= 2.f;
            v.w = 0.0;

            if (!_luminosityVar.empty()) {
                float lumS = _fullData[p + _variableDataPositionMap[_luminosityVar]] *
                             _sluminosity;
                u *= lumS;
                v *= lumS;
            }

            u *= _scaleFactor;
            v *= _scaleFactor;

            RenderingPlane plane;
            plane.planeIndex = _fullData[p + _textureVariableIndex];

            // JCC: Ask Abbott about these points refeering to a non-existing texture.
            if (plane.planeIndex == 30) {
                plane.planeIndex = -1;
            }

            glGenVertexArrays(1, &plane.vao);
            glGenBuffers(1, &plane.vbo);

            glm::vec4 vertex0 = transformedPos - u - v; // same as 3
            glm::vec4 vertex1 = transformedPos + u + v; // same as 5
            glm::vec4 vertex2 = transformedPos - u + v;
            glm::vec4 vertex4 = transformedPos + u - v;

            float scale = 0.0;
            switch (_unit) {
            case Meter:
                scale = 1.0;
                break;
            case Kilometer:
                scale = 1e3;
                break;
            case Parsec:
                scale = PARSEC;
                break;
            case Kiloparsec:
                scale = 1e3 * PARSEC;
                break;
            case Megaparsec:
                scale = 1e6 * PARSEC;
                break;
            case Gigaparsec:
                scale = 1e9 * PARSEC;
                break;
            case GigalightYears:
                scale = 306391534.73091 * PARSEC;
                break;
            }

            for (int i = 0; i < 3; ++i) {
                maxSize = maxSize > vertex0[i] ? maxSize : vertex0[i];
                maxSize = maxSize > vertex1[i] ? maxSize : vertex1[i];
                maxSize = maxSize > vertex2[i] ? maxSize : vertex2[i];
                maxSize = maxSize > vertex4[i] ? maxSize : vertex4[i];
            }

            vertex0 *= static_cast<float>(scale);
            vertex1 *= static_cast<float>(scale);
            vertex2 *= static_cast<float>(scale);
            vertex4 *= static_cast<float>(scale);

            GLfloat vertexData[] = {
                //      x      y     z     w           s    t
                vertex0.x, vertex0.y, vertex0.z, 1.f, 0.f, 0.f,
                vertex1.x, vertex1.y, vertex1.z, 1.f, 1.f, 1.f,
                vertex2.x, vertex2.y, vertex2.z, 1.f, 0.f, 1.f,
                vertex0.x, vertex0.y, vertex0.z, 1.f, 0.f, 0.f,
                vertex4.x, vertex4.y, vertex4.z, 1.f, 1.f, 0.f,
                vertex1.x, vertex1.y, vertex1.z, 1.f, 1.f, 1.f,
            };

            std::memcpy(plane.vertexData, vertexData, sizeof(vertexData));

            glBindVertexArray(plane.vao);
            glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);
            glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(plane.vertexData),
                plane.vertexData,
                GL_STATIC_DRAW
            );
            // in_position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(
                0,
                4,
                GL_FLOAT,
                GL_FALSE,
                sizeof(GLfloat) * 6,
                nullptr
            );

            // texture coords
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(
                1,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(GLfloat) * 6,
                reinterpret_cast<GLvoid*>(sizeof(GLfloat) * 4)
            );

            _renderingPlanesArray.push_back(plane);
        }

        glBindVertexArray(0);

        _dataIsDirty = false;

        _fadeInDistance.setMaxValue(glm::vec2(10.0f * maxSize));
    }

    if (_hasLabel && _labelDataIsDirty) {
        _labelDataIsDirty = false;
    }

    // Sort planes by texture index
    if (!_renderingPlanesArray.empty()) {
        std::sort(_renderingPlanesArray.begin(), _renderingPlanesArray.end(),
            [](const RenderingPlane& planeA, const RenderingPlane& planeB) {
            return planeA.planeIndex < planeB.planeIndex;
        });
    }
}

} // namespace openspace
