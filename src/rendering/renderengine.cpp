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

#include <openspace/rendering/renderengine.h>

#include <openspace/util/syncdata.h>

#include <openspace/openspace.h>
#include <openspace/engine/configurationmanager.h>
#include <openspace/engine/openspaceengine.h>
#include <openspace/engine/wrapper/windowwrapper.h>
#include <openspace/interaction/navigationhandler.h>
#include <openspace/interaction/luaconsole.h>
#include <openspace/mission/missionmanager.h>
#include <openspace/performance/performancemanager.h>
#include <openspace/performance/performancemeasurement.h>
#include <openspace/rendering/abufferrenderer.h>
#include <openspace/rendering/dashboard.h>
#include <openspace/rendering/dashboarditem.h>
#include <openspace/rendering/framebufferrenderer.h>
#include <openspace/rendering/deferredcastermanager.h>
#include <openspace/rendering/raycastermanager.h>
#include <openspace/rendering/renderer.h>
#include <openspace/rendering/screenspacerenderable.h>
#include <openspace/scene/scene.h>
#include <openspace/scene/scenegraphnode.h>
#include <openspace/scripting/scriptengine.h>
#include <openspace/util/camera.h>
#include <openspace/util/time.h>
#include <openspace/util/timemanager.h>
#include <openspace/util/screenlog.h>

#include <ghoul/glm.h>
#include <ghoul/filesystem/filesystem.h>
#include <ghoul/font/font.h>
#include <ghoul/font/fontmanager.h>
#include <ghoul/font/fontrenderer.h>
#include <ghoul/io/texture/texturereader.h>
#include <ghoul/io/texture/texturereadercmap.h>
#include <ghoul/opengl/programobject.h>
#include <ghoul/systemcapabilities/openglcapabilitiescomponent.h>

#ifdef GHOUL_USE_DEVIL
#include <ghoul/io/texture/texturereaderdevil.h>
#endif //GHOUL_USE_DEVIL
#ifdef GHOUL_USE_FREEIMAGE
#include <ghoul/io/texture/texturereaderfreeimage.h>
#endif // GHOUL_USE_FREEIMAGE

#ifdef GHOUL_USE_SOIL
#include <ghoul/io/texture/texturereadersoil.h>
#include <ghoul/io/texture/texturewriter.h>
#include <ghoul/io/texture/texturewritersoil.h>
#endif //GHOUL_USE_SOIL

#ifdef GHOUL_USE_STB_IMAGE
#include <ghoul/io/texture/texturereaderstb.h>
#endif // GHOUL_USE_STB_IMAGE

#include <array>
#include <stack>

#include "renderengine_lua.inl"

namespace {
    constexpr const char* _loggerCat = "RenderEngine";

    constexpr const char* KeyRenderingMethod = "RenderingMethod";
    constexpr const std::chrono::seconds ScreenLogTimeToLive(15);
    constexpr const char* DefaultRenderingMethod = "ABuffer";
    constexpr const char* RenderFsPath = "${SHADERS}/render.frag";

    constexpr const char* KeyFontMono = "Mono";
    constexpr const char* KeyFontLight = "Light";

    static const openspace::properties::Property::PropertyInfo PerformanceInfo = {
        "PerformanceMeasurements",
        "Performance Measurements",
        "If this value is enabled, detailed performance measurements about the updates "
        "and rendering of the scene graph nodes are collected each frame. These values "
        "provide some information about the impact of individual nodes on the overall "
        "performance."
    };

    static const openspace::properties::Property::PropertyInfo ShowDateInfo = {
        "ShowDate",
        "Show Date Information",
        "This values determines whether the date will be printed in the top left corner "
        "of the rendering window if a regular rendering window is used (as opposed to a "
        "fisheye rendering, for example)."
    };

    static const openspace::properties::Property::PropertyInfo ShowInfoInfo = {
        "ShowInfo",
        "Show Rendering Information",
        "This value determines whether the rendering info, which is the delta time and "
        "the frame time, is shown in the top left corner of the rendering window if a "
        "regular rendering window is used (as opposed to a fisheye rendering, for "
        "example)."
    };

    static const openspace::properties::Property::PropertyInfo ShowOverlaySlavesInfo = {
        "ShowOverlayOnSlaves",
        "Show Overlay Information on Slaves",
        "If this value is enabled, the overlay information text is also automatically "
        "rendered on the slave nodes. This values is disabled by default."
    };

    static const openspace::properties::Property::PropertyInfo ShowLogInfo = {
        "ShowLog",
        "Show the on-screen log",
        "This value determines whether the on-screen log will be shown or hidden. Even "
        "if it is shown, all 'Debug' and 'Trace' level messages are omitted from this "
        "log."
    };

    static const openspace::properties::Property::PropertyInfo ShowVersionInfo = {
        "ShowVersion",
        "Shows the version on-screen information",
        "This value determines whether the Git version information (branch and commit) "
        "hash are shown on the screen."
    };

    static const openspace::properties::Property::PropertyInfo ShowCameraInfo = {
        "ShowCamera",
        "Shows information about the current camera state, such as friction",
        "This value determines whether the information about the current camrea state is "
        "shown on the screen"
    };

    static const openspace::properties::Property::PropertyInfo TakeScreenshotInfo = {
        "TakeScreenshot",
        "Take Screenshot",
        "If this property is triggered, a screenshot is taken and stored in the current "
        "working directory (which is the same directory where the OpenSpace.exe) is "
        "located in most cases. The images are prefixed with 'SGCT' and postfixed with "
        "the number of frames. This function will silently overwrite images that are "
        "already present in the folder."
    };

    static const openspace::properties::Property::PropertyInfo ApplyWarpingInfo = {
        "ApplyWarpingScreenshot",
        "Apply Warping to Screenshots",
        "This value determines whether a warping should be applied before taking a "
        "screenshot. If it is enabled, all post processing is applied as well, which "
        "includes everything rendered on top of the rendering, such as the user "
        "interface."
    };

    static const openspace::properties::Property::PropertyInfo ShowFrameNumberInfo = {
        "ShowFrameNumber",
        "Show Frame Number",
        "If this value is enabled, the current frame number is rendered into the window."
    };

    static const openspace::properties::Property::PropertyInfo DisableMasterInfo = {
        "DisableMasterRendering",
        "Disable Master Rendering",
        "If this value is enabled, the rendering on the master node will be disabled. "
        "Every other aspect of the application will be unaffected by this and it will "
        "still respond to user input. This setting is reasonably only useful in the case "
        "of multi-pipeline environments, such as planetariums, where the output of the "
        "master node is not required and performance can be gained by disabling it."
    };

    static const openspace::properties::Property::PropertyInfo DisableTranslationInfo = {
        "DisableSceneTranslationOnMaster",
        "Disable Scene Translation on Master",
        "If this value is enabled, any scene translations such as specified in, for "
        "example an SGCT configuration, is disabled for the master node. This setting "
        "can be useful if a planetarium environment requires a scene translation to be "
        "applied, which would otherwise make interacting through the master node "
        "difficult."
    };

    static const openspace::properties::Property::PropertyInfo AaSamplesInfo = {
        "AaSamples",
        "Number of Anti-aliasing samples",
        "This value determines the number of anti-aliasing samples to be used in the "
        "rendering for the MSAA method."
    };

    static const openspace::properties::Property::PropertyInfo HDRExposureInfo = {
        "HDRExposure",
        "HDR Exposure",
        "This value determines the amount of light per unit area reaching the "
        "equivalent of an electronic image sensor."
    };

    static const openspace::properties::Property::PropertyInfo BackgroundExposureInfo = {
        "Background Exposure",
        "BackgroundExposure",
        "This value determines the amount of light per unit area reaching the "
        "equivalent of an electronic image sensor for the background image."
    };

    static const openspace::properties::Property::PropertyInfo GammaInfo = {
        "Gamma",
        "Gamma Correction",
        "Gamma, is the nonlinear operation used to encode and decode luminance or "
        "tristimulus values in the image."
    };
} // namespace


namespace openspace {

RenderEngine::RenderEngine()
    : properties::PropertyOwner({ "RenderEngine" })
    , _camera(nullptr)
    , _scene(nullptr)
    , _raycasterManager(nullptr)
    , _deferredcasterManager(nullptr)
    , _doPerformanceMeasurements(PerformanceInfo)
    , _performanceManager(nullptr)
    , _renderer(nullptr)
    , _rendererImplementation(RendererImplementation::Invalid)
    , _log(nullptr)
    , _showOverlayOnSlaves(ShowOverlaySlavesInfo, false)
    , _showLog(ShowLogInfo, true)
    , _showVersionInfo(ShowVersionInfo, true)
    , _showCameraInfo(ShowCameraInfo, true)
    , _takeScreenshot(TakeScreenshotInfo)
    , _shouldTakeScreenshot(false)
    , _applyWarping(ApplyWarpingInfo, false)
    , _showFrameNumber(ShowFrameNumberInfo, false)
    , _disableMasterRendering(DisableMasterInfo, false)
    , _disableSceneTranslationOnMaster(DisableTranslationInfo, false)
    , _globalBlackOutFactor(1.f)
    , _fadeDuration(2.f)
    , _currentFadeTime(0.f)
    , _fadeDirection(0)
    , _nAaSamples(AaSamplesInfo, 4, 1, 16)
    , _hdrExposure(HDRExposureInfo, 0.4f, 0.01f, 10.0f)
    , _hdrBackground(BackgroundExposureInfo, 2.8f, 0.01f, 10.0f)
    , _gamma(GammaInfo, 2.2f, 0.01f, 10.0f)
    , _frameNumber(0)
    , _screenSpaceOwner({ "ScreenSpace" })
{
    _doPerformanceMeasurements.onChange([this](){
        if (_doPerformanceMeasurements) {
            if (!_performanceManager) {
                std::string loggingDir = "${BASE}";
                constexpr const char* KeyDir = ConfigurationManager::LoggingDirectory;
                if (OsEng.configurationManager().hasKey(KeyDir)) {
                    loggingDir = OsEng.configurationManager().value<std::string>(KeyDir);
                }

                std::string prefix = "PM-";
                constexpr const char* KeyPrefix =
                                           ConfigurationManager::LoggingPerformancePrefix;
                if (OsEng.configurationManager().hasKey(KeyPrefix)) {
                    prefix = OsEng.configurationManager().value<std::string>(KeyPrefix);
                }

                _performanceManager = std::make_shared<performance::PerformanceManager>(
                    loggingDir,
                    prefix
                );
            }
        }
        else {
            _performanceManager = nullptr;
        }

    });
    addProperty(_doPerformanceMeasurements);

    addProperty(_showOverlayOnSlaves);
    addProperty(_showLog);
    addProperty(_showVersionInfo);
    addProperty(_showCameraInfo);

    _nAaSamples.onChange([this](){
        if (_renderer) {
            _renderer->setNAaSamples(_nAaSamples);
        }
    });
    _hdrExposure.onChange([this]() {
        if (_renderer) {
            _renderer->setHDRExposure(_hdrExposure);
        }
    });
    _hdrBackground.onChange([this]() {
        if (_renderer) {
            _renderer->setHDRBackground(_hdrBackground);
        }
    });
    _gamma.onChange([this]() {
        if (_renderer) {
            _renderer->setGamma(_gamma);
        }
    });

    addProperty(_nAaSamples);
    addProperty(_hdrExposure);
    addProperty(_hdrBackground);
    addProperty(_gamma);
    addProperty(_applyWarping);

    _takeScreenshot.onChange([this](){
        _shouldTakeScreenshot = true;
    });
    addProperty(_takeScreenshot);

    addProperty(_showFrameNumber);

    addProperty(_disableSceneTranslationOnMaster);
    addProperty(_disableMasterRendering);
}

RenderEngine::~RenderEngine() {}

void RenderEngine::setRendererFromString(const std::string& renderingMethod) {
    _rendererImplementation = rendererFromString(renderingMethod);

    std::unique_ptr<Renderer> newRenderer = nullptr;
    switch (_rendererImplementation) {
    case RendererImplementation::Framebuffer:
        newRenderer = std::make_unique<FramebufferRenderer>();
        break;
    case RendererImplementation::ABuffer:
        newRenderer = std::make_unique<ABufferRenderer>();
        break;
    case RendererImplementation::Invalid:
        LFATAL(fmt::format("Rendering method '{}' not available", renderingMethod));
    }

    setRenderer(std::move(newRenderer));
}

void RenderEngine::initialize() {
    _frameNumber = 0;
    std::string renderingMethod = DefaultRenderingMethod;

    // If the user specified a rendering method that he would like to use, use that
    ConfigurationManager& confManager = OsEng.configurationManager();
    if (confManager.hasKeyAndValue<std::string>(KeyRenderingMethod)) {
        renderingMethod = confManager.value<std::string>(KeyRenderingMethod);
    }
    else {
        using Version = ghoul::systemcapabilities::Version;

        // The default rendering method has a requirement of OpenGL 4.3, so if we are
        // below that, we will fall back to frame buffer operation
        if (OpenGLCap.openGLVersion() < Version{ 4,3,0 }) {
            LINFO("Falling back to framebuffer implementation due to OpenGL limitations");
            renderingMethod = "Framebuffer";
        }
    }

    if (confManager.hasKey(ConfigurationManager::KeyDisableMasterRendering)) {
        _disableMasterRendering = confManager.value<bool>(
            ConfigurationManager::KeyDisableMasterRendering
            );
    }

    if (confManager.hasKey(ConfigurationManager::KeyDisableSceneOnMaster)) {
        _disableSceneTranslationOnMaster = confManager.value<bool>(
            ConfigurationManager::KeyDisableSceneOnMaster
            );
    }

    _raycasterManager = std::make_unique<RaycasterManager>();
    _deferredcasterManager = std::make_unique<DeferredcasterManager>();
    _nAaSamples = OsEng.windowWrapper().currentNumberOfAaSamples();

    LINFO(fmt::format("Setting renderer from string: {}", renderingMethod));
    setRendererFromString(renderingMethod);

#ifdef GHOUL_USE_DEVIL
    ghoul::io::TextureReader::ref().addReader(
        std::make_shared<ghoul::io::TextureReaderDevIL>()
    );
#endif // GHOUL_USE_DEVIL
#ifdef GHOUL_USE_FREEIMAGE
    ghoul::io::TextureReader::ref().addReader(
        std::make_shared<ghoul::io::TextureReaderFreeImage>()
    );
#endif // GHOUL_USE_FREEIMAGE
#ifdef GHOUL_USE_SOIL
    ghoul::io::TextureReader::ref().addReader(
        std::make_shared<ghoul::io::TextureReaderSOIL>()
    );
    ghoul::io::TextureWriter::ref().addWriter(
        std::make_shared<ghoul::io::TextureWriterSOIL>()
    );
#endif // GHOUL_USE_SOIL
#ifdef GHOUL_USE_STB_IMAGE
    ghoul::io::TextureReader::ref().addReader(
        std::make_shared<ghoul::io::TextureReaderSTB>()
    );    
#endif // GHOUL_USE_STB_IMAGE

    ghoul::io::TextureReader::ref().addReader(
        std::make_shared<ghoul::io::TextureReaderCMAP>()
    );

    MissionManager::initialize();
}

void RenderEngine::initializeGL() {
    LTRACE("RenderEngine::initializeGL(begin)");
    // TODO:    Fix the power scaled coordinates in such a way that these
    //            values can be set to more realistic values

    // set the close clip plane and the far clip plane to extreme values while in
    // development
    OsEng.windowWrapper().setNearFarClippingPlane(0.001f, 1000.f);

    try {
        const float fontSizeBig = 50.f;
        _fontBig = OsEng.fontManager().font(KeyFontMono, fontSizeBig);
        const float fontSizeTime = 15.f;
        _fontDate = OsEng.fontManager().font(KeyFontMono, fontSizeTime);
        const float fontSizeMono = 10.f;
        _fontInfo = OsEng.fontManager().font(KeyFontMono, fontSizeMono);
        const float fontSizeLight = 8.f;
        _fontLog = OsEng.fontManager().font(KeyFontLight, fontSizeLight);
    } catch (const ghoul::fontrendering::Font::FreeTypeException& e) {
        LERROR(e.what());
        throw;
    }

    LINFO("Initializing Log");
    std::unique_ptr<ScreenLog> log = std::make_unique<ScreenLog>(ScreenLogTimeToLive);
    _log = log.get();
    ghoul::logging::LogManager::ref().addLog(std::move(log));

    for (std::shared_ptr<ScreenSpaceRenderable>& ssr : _screenSpaceRenderables) {
        ssr->initializeGL();
    }

    LINFO("Finished initializing GL");
    LTRACE("RenderEngine::initializeGL(end)");
}

void RenderEngine::deinitialize() {
    for (std::shared_ptr<ScreenSpaceRenderable>& ssr : _screenSpaceRenderables) {
        ssr->deinitialize();
    }

    MissionManager::deinitialize();
}

void RenderEngine::deinitializeGL() {
    for (std::shared_ptr<ScreenSpaceRenderable>& ssr : _screenSpaceRenderables) {
        ssr->deinitializeGL();
    }
}

void RenderEngine::updateScene() {
    if (!_scene) {
        return;
    }

    _scene->updateInterpolations();

    const Time& currentTime = OsEng.timeManager().time();
    _scene->update({
        { glm::dvec3(0), glm::dmat3(1), 1.0 },
        currentTime,
        _performanceManager != nullptr
    });

    LTRACE("RenderEngine::updateSceneGraph(end)");
}

void RenderEngine::updateShaderPrograms() {
    for (ghoul::opengl::ProgramObject* program : _programs) {
        try {
            if (program->isDirty()) {
                program->rebuildFromFile();
            }
        }
        catch (const ghoul::opengl::ShaderObject::ShaderCompileError& e) {
            LERRORC(e.component, e.what());
        }
    }
}

void RenderEngine::updateRenderer() {
    bool windowResized = OsEng.windowWrapper().windowHasResized();

    if (windowResized) {
        _renderer->setResolution(renderingResolution());

        using FR = ghoul::fontrendering::FontRenderer;

        FR::defaultRenderer().setFramebufferSize(fontResolution());
        FR::defaultProjectionRenderer().setFramebufferSize(renderingResolution());
    }

    _renderer->update();
}

void RenderEngine::updateScreenSpaceRenderables() {
    for (std::shared_ptr<ScreenSpaceRenderable>& ssr : _screenSpaceRenderables) {
        ssr->update();
    }
}

glm::ivec2 RenderEngine::renderingResolution() const {
    if (OsEng.windowWrapper().isRegularRendering()) {
        return OsEng.windowWrapper().currentWindowResolution();
    }
    else {
        return OsEng.windowWrapper().currentDrawBufferResolution();
    }
}

glm::ivec2 RenderEngine::fontResolution() const {
    std::string value;
    bool hasValue = OsEng.configurationManager().getValue(
        ConfigurationManager::KeyOnScreenTextScaling,
        value
    );
    if (hasValue && value == "framebuffer") {
        return OsEng.windowWrapper().currentWindowResolution();
    }
    else {
        // The default is to use the window size
        return OsEng.windowWrapper().currentWindowSize();
    }
}

void RenderEngine::updateFade() {
    // Temporary fade funtionality
    const float fadedIn = 1.0;
    const float fadedOut = 0.0;
    // Don't restart the fade if you've already done it in that direction
    const bool isFadedIn = (_fadeDirection > 0 && _globalBlackOutFactor == fadedIn);
    const bool isFadedOut = (_fadeDirection < 0 && _globalBlackOutFactor == fadedOut);
    if (isFadedIn || isFadedOut) {
        _fadeDirection = 0;
    }

    if (_fadeDirection != 0) {
        if (_currentFadeTime > _fadeDuration) {
            _globalBlackOutFactor = _fadeDirection > 0 ? fadedIn : fadedOut;
            _fadeDirection = 0;
        }
        else {
            if (_fadeDirection < 0) {
                _globalBlackOutFactor = glm::smoothstep(
                    1.f,
                    0.f,
                    _currentFadeTime / _fadeDuration
                );
            }
            else {
                _globalBlackOutFactor = glm::smoothstep(
                    0.f,
                    1.f,
                    _currentFadeTime / _fadeDuration
                );
            }
            _currentFadeTime += static_cast<float>(
                OsEng.windowWrapper().averageDeltaTime()
                );
        }
    }
}

void RenderEngine::render(const glm::mat4& sceneMatrix, const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix)
{
    LTRACE("RenderEngine::render(begin)");
    WindowWrapper& wrapper = OsEng.windowWrapper();
    if (_camera) {
        if (_disableSceneTranslationOnMaster && wrapper.isMaster()) {
            _camera->sgctInternal.setViewMatrix(viewMatrix);
        }
        else {
            _camera->sgctInternal.setViewMatrix(viewMatrix * sceneMatrix);
            _camera->sgctInternal.setSceneMatrix(sceneMatrix);
        }
    }
    _camera->sgctInternal.setProjectionMatrix(projectionMatrix);

    bool masterEnabled = wrapper.isMaster() ? !_disableMasterRendering : true;
    if (masterEnabled && !wrapper.isGuiWindow() && _globalBlackOutFactor > 0.f) {
        _renderer->render(_globalBlackOutFactor, _performanceManager != nullptr);
    }

    if (_showFrameNumber) {
        const glm::vec2 penPosition = glm::vec2(
            fontResolution().x / 2 - 50,
            fontResolution().y / 3
        );

        RenderFont(*_fontBig, penPosition, "%i", _frameNumber);
    }

    ++_frameNumber;

    for (std::shared_ptr<ScreenSpaceRenderable>& ssr : _screenSpaceRenderables) {
        if (ssr->isEnabled() && ssr->isReady()) {
            ssr->render();
        }
    }
    LTRACE("RenderEngine::render(end)");
}

void RenderEngine::renderOverlays(const ShutdownInformation& info) {
    const bool isMaster = OsEng.windowWrapper().isMaster();
    if (isMaster || _showOverlayOnSlaves) {
        renderScreenLog();
        renderVersionInformation();
        renderDashboard();

        if (!info.inShutdown) {
            // We render the camera information in the same location as the shutdown info
            // and we won't need this if we are shutting down
            renderCameraInformation();
        }
        else {
            // If we are in shutdown mode, we can display the remaining time
            renderShutdownInformation(info.timer, info.waitTime);
        }
    }
}

void RenderEngine::renderShutdownInformation(float timer, float fullTime) {
    timer = timer < 0.f ? 0.f : timer;

    auto size = ghoul::fontrendering::FontRenderer::defaultRenderer().boundingBox(
        *_fontDate,
        "Shutdown in: %.2fs/%.2fs",
        timer,
        fullTime
    );

    glm::vec2 penPosition = glm::vec2(
        fontResolution().x - size.boundingBox.x - 10,
        fontResolution().y - size.boundingBox.y
    );

    RenderFontCr(
        *_fontDate,
        penPosition,
        "Shutdown in: %.2fs/%.2fs",
        timer,
        fullTime
    );

    RenderFontCr(
        *_fontDate,
        penPosition,
        "%s",
        // Important: length of this string is the same as the shutdown time text
        // to make them align
        "Press ESC again to abort"
    );
}

void RenderEngine::renderDashboard() {
    std::unique_ptr<performance::PerformanceMeasurement> perf;
    if (_performanceManager) {
        perf = std::make_unique<performance::PerformanceMeasurement>(
            "Main Dashboard::render",
            OsEng.renderEngine().performanceManager()
            );
    }
    glm::vec2 penPosition = glm::vec2(
        10.f,
        fontResolution().y
    );

    penPosition.y -= OsEng.console().currentHeight();

    OsEng.dashboard().render(penPosition);
}

void RenderEngine::postDraw() {
    Time& currentTime = OsEng.timeManager().time();
    if (currentTime.timeJumped()) {
        currentTime.setTimeJumped(false);
    }

    if (_shouldTakeScreenshot) {
        // We only create the directory here, as we don't want to spam the users
        // screenshot folder everytime we start OpenSpace even when we are not taking any
        // screenshots. So the first time we actually take one, we create the folder:
        if (!FileSys.directoryExists(absPath("${THIS_SCREENSHOT_PATH}"))) {
            FileSys.createDirectory(
                absPath("${THIS_SCREENSHOT_PATH}"),
                ghoul::filesystem::FileSystem::Recursive::Yes
            );
        }

        OsEng.windowWrapper().takeScreenshot(_applyWarping);
        _shouldTakeScreenshot = false;
    }

    if (_performanceManager) {
        _performanceManager->storeScenePerformanceMeasurements(
            scene()->allSceneGraphNodes()
        );
    }
}

Scene* RenderEngine::scene() {
    return _scene;
}

RaycasterManager& RenderEngine::raycasterManager() {
    return *_raycasterManager;
}

DeferredcasterManager& RenderEngine::deferredcasterManager() {
    return *_deferredcasterManager;
}

void RenderEngine::setScene(Scene* scene) {
    _scene = scene;
    if (_renderer) {
        _renderer->setScene(scene);
    }
}

void RenderEngine::setCamera(Camera* camera) {
    _camera = camera;
    if (_renderer) {
        _renderer->setCamera(camera);
    }
}

Camera* RenderEngine::camera() const {
    return _camera;
}

Renderer* RenderEngine::renderer() const {
    return _renderer.get();
}

RenderEngine::RendererImplementation RenderEngine::rendererImplementation() const {
    return _rendererImplementation;
}

float RenderEngine::globalBlackOutFactor() {
    return _globalBlackOutFactor;
}

void RenderEngine::setGlobalBlackOutFactor(float opacity) {
    _globalBlackOutFactor = opacity;
}

void RenderEngine::startFading(int direction, float fadeDuration) {
    _fadeDirection = direction;
    _fadeDuration = fadeDuration;
    _currentFadeTime = 0.f;
}

/**
* Build a program object for rendering with the used renderer
*/
std::unique_ptr<ghoul::opengl::ProgramObject> RenderEngine::buildRenderProgram(
    std::string name, std::string vsPath,
    std::string fsPath, const ghoul::Dictionary& data)
{

    ghoul::Dictionary dict = data;

    // set path to the current renderer's main fragment shader
    dict.setValue("rendererData", _rendererData);
    // parameterize the main fragment shader program with specific contents.
    // fsPath should point to a shader file defining a Fragment getFragment() function
    // instead of a void main() setting glFragColor, glFragDepth, etc.
    dict.setValue("fragmentPath", fsPath);

    using namespace ghoul::opengl;
    std::unique_ptr<ProgramObject> program = ProgramObject::Build(
        name,
        vsPath,
        absPath(RenderFsPath),
        dict
    );

    if (program) {
        _programs.push_back(program.get());
    }
    return program;
}

/**
* Build a program object for rendering with the used renderer
*/
std::unique_ptr<ghoul::opengl::ProgramObject> RenderEngine::buildRenderProgram(
    std::string name, std::string vsPath,
    std::string fsPath, std::string csPath,
    const ghoul::Dictionary& data)
{
    ghoul::Dictionary dict = data;
    dict.setValue("rendererData", _rendererData);

    // parameterize the main fragment shader program with specific contents.
    // fsPath should point to a shader file defining a Fragment getFragment() function
    // instead of a void main() setting glFragColor, glFragDepth, etc.
    dict.setValue("fragmentPath", fsPath);

    using namespace ghoul::opengl;
    std::unique_ptr<ProgramObject> program = ProgramObject::Build(
        name,
        vsPath,
        absPath(RenderFsPath),
        csPath,
        dict
    );

    if (program) {
        _programs.push_back(program.get());
    }
    return program;
}

void RenderEngine::removeRenderProgram(
    const std::unique_ptr<ghoul::opengl::ProgramObject>& program)
{
    if (!program) {
        return;
    }

    auto it = std::find(
        _programs.begin(),
        _programs.end(),
        program.get()
    );

    if (it != _programs.end()) {
        _programs.erase(it);
    }
}

/**
* Set renderer data
* Called from the renderer, whenever it needs to update
* the dictionary of all rendering programs.
*/
void RenderEngine::setRendererData(const ghoul::Dictionary& data) {
    _rendererData = data;
    for (ghoul::opengl::ProgramObject* program : _programs) {
        ghoul::Dictionary dict = program->dictionary();
        dict.setValue("rendererData", _rendererData);
        program->setDictionary(dict);
    }
}

/**
* Set resolve data
* Called from the renderer, whenever it needs to update
* the dictionary of all post rendering programs.
*/
void RenderEngine::setResolveData(const ghoul::Dictionary& data) {
    _resolveData = data;
    for (ghoul::opengl::ProgramObject* program : _programs) {
        ghoul::Dictionary dict = program->dictionary();
        dict.setValue("resolveData", _resolveData);
        program->setDictionary(dict);
    }
}

/**
* Set raycasting uniforms on the program object, and setup raycasting.
*/
void RenderEngine::preRaycast(ghoul::opengl::ProgramObject& programObject) {
    _renderer->preRaycast(programObject);
}

/**
* Tear down raycasting for the specified program object.
*/
void RenderEngine::postRaycast(ghoul::opengl::ProgramObject& programObject) {
    _renderer->postRaycast(programObject);
}

/**
* Set renderer
*/
void RenderEngine::setRenderer(std::unique_ptr<Renderer> renderer) {
    if (_renderer) {
        _renderer->deinitialize();
    }

    _renderer = std::move(renderer);
    _renderer->setResolution(renderingResolution());
    _renderer->setNAaSamples(_nAaSamples);
    _renderer->setHDRExposure(_hdrExposure);
    _renderer->initialize();
    _renderer->setCamera(_camera);
    _renderer->setScene(_scene);
}

scripting::LuaLibrary RenderEngine::luaLibrary() {
    return{
        "",
        {
            {
                "setRenderer",
                &luascriptfunctions::setRenderer,
                {},
                "string",
                "Sets the renderer (ABuffer or FrameBuffer)"
            },
            {
                "toggleFade",
                &luascriptfunctions::toggleFade,
                {},
                "number",
                "Toggles fading in or out"
            },
            {
                "fadeIn",
                &luascriptfunctions::fadeIn,
                {},
                "number",
                ""
            },
            {
                "fadeOut",
                &luascriptfunctions::fadeOut,
                {},
                "number",
                ""
            },
            {
                "addScreenSpaceRenderable",
                &luascriptfunctions::addScreenSpaceRenderable,
                {},
                "table",
                "Will create a ScreenSpaceRenderable from a lua Table and add it in the "
                "RenderEngine"
            },
            {
                "removeScreenSpaceRenderable",
                &luascriptfunctions::removeScreenSpaceRenderable,
                {},
                "string",
                "Given a ScreenSpaceRenderable name this script will remove it from the "
                "renderengine"
            },
        },
    };
}

bool RenderEngine::doesPerformanceMeasurements() const {
    return _performanceManager != nullptr;
}

std::shared_ptr<performance::PerformanceManager> RenderEngine::performanceManager() {
    return _performanceManager;
}

void RenderEngine::addScreenSpaceRenderable(std::shared_ptr<ScreenSpaceRenderable> s) {
    s->initialize();
    s->initializeGL();

    _screenSpaceOwner.addPropertySubOwner(s.get());

    _screenSpaceRenderables.push_back(std::move(s));
}

void RenderEngine::removeScreenSpaceRenderable(std::shared_ptr<ScreenSpaceRenderable> s) {
    auto it = std::find(
        _screenSpaceRenderables.begin(),
        _screenSpaceRenderables.end(),
        s
    );

    if (it != _screenSpaceRenderables.end()) {
        s->deinitialize();
        _screenSpaceOwner.removePropertySubOwner(s.get());

        _screenSpaceRenderables.erase(it);
    }
}

void RenderEngine::removeScreenSpaceRenderable(const std::string& name) {
    std::shared_ptr<ScreenSpaceRenderable> s = screenSpaceRenderable(name);
    if (s) {
        removeScreenSpaceRenderable(s);
    }
}

std::shared_ptr<ScreenSpaceRenderable> RenderEngine::screenSpaceRenderable(
                                                            const std::string& identifier)
{
    auto it = std::find_if(
        _screenSpaceRenderables.begin(),
        _screenSpaceRenderables.end(),
        [&identifier](const std::shared_ptr<ScreenSpaceRenderable>& s) {
            return s->identifier() == identifier;
        }
    );

    if (it != _screenSpaceRenderables.end()) {
        return *it;
    }
    else {
        return nullptr;
    }
}

std::vector<ScreenSpaceRenderable*> RenderEngine::screenSpaceRenderables() const {
    std::vector<ScreenSpaceRenderable*> res(_screenSpaceRenderables.size());
    std::transform(
        _screenSpaceRenderables.begin(),
        _screenSpaceRenderables.end(),
        res.begin(),
        [](std::shared_ptr<ScreenSpaceRenderable> p) { return p.get(); }
    );
    return res;
}

RenderEngine::RendererImplementation RenderEngine::rendererFromString(
                                                            const std::string& impl) const
{
    const std::map<std::string, RenderEngine::RendererImplementation> RenderingMethods = {
        { "ABuffer", RendererImplementation::ABuffer },
        { "Framebuffer", RendererImplementation::Framebuffer }
    };

    if (RenderingMethods.find(impl) != RenderingMethods.end()) {
        return RenderingMethods.at(impl);
    }
    else {
        return RendererImplementation::Invalid;
    }
}

void RenderEngine::renderCameraInformation() {
    if (!_showCameraInfo) {
        return;
    }

    const glm::vec4 enabled = glm::vec4(0.2f, 0.75f, 0.2f, 1.f);
    const glm::vec4 disabled = glm::vec4(0.55f, 0.2f, 0.2f, 1.f);

    using FR = ghoul::fontrendering::FontRenderer;

    FR::BoundingBoxInformation rotationBox = FR::defaultRenderer().boundingBox(
        *_fontInfo,
        "%s",
        "Rotation"
    );

    float penPosY = fontResolution().y - rotationBox.boundingBox.y;

    const float ySeparation = 5.f;
    const float xSeparation = 5.f;

    interaction::OrbitalNavigator nav = OsEng.navigationHandler().orbitalNavigator();

    FR::defaultRenderer().render(
        *_fontInfo,
        glm::vec2(fontResolution().x - rotationBox.boundingBox.x - xSeparation, penPosY),
        nav.hasRotationalFriction() ? enabled : disabled,
        "%s",
        "Rotation"
    );
    penPosY -= rotationBox.boundingBox.y + ySeparation;

    FR::BoundingBoxInformation zoomBox = FR::defaultRenderer().boundingBox(
        *_fontInfo,
        "%s",
        "Zoom"
    );

    FR::defaultRenderer().render(
        *_fontInfo,
        glm::vec2(fontResolution().x - zoomBox.boundingBox.x - xSeparation, penPosY),
        nav.hasZoomFriction() ? enabled : disabled,
        "%s",
        "Zoom"
    );
    penPosY -= zoomBox.boundingBox.y + ySeparation;

    FR::BoundingBoxInformation rollBox = FR::defaultRenderer().boundingBox(
        *_fontInfo,
        "%s",
        "Roll"
    );

    FR::defaultRenderer().render(
        *_fontInfo,
        glm::vec2(fontResolution().x - rollBox.boundingBox.x - xSeparation, penPosY),
        nav.hasRollFriction() ? enabled : disabled,
        "%s",
        "Roll"
    );
}

void RenderEngine::renderVersionInformation() {
    if (!_showVersionInfo) {
        return;
    }

    using FR = ghoul::fontrendering::FontRenderer;

    FR::BoundingBoxInformation versionBox = FR::defaultRenderer().boundingBox(
        *_fontInfo,
        "%s",
        OPENSPACE_VERSION_STRING_FULL
    );

    FR::BoundingBoxInformation commitBox = FR::defaultRenderer().boundingBox(
        *_fontInfo,
        "%s@%s",
        OPENSPACE_GIT_BRANCH,
        OPENSPACE_GIT_COMMIT
    );

    FR::defaultRenderer().render(
        *_fontInfo,
        glm::vec2(
            fontResolution().x - versionBox.boundingBox.x - 10.f,
            5.f
        ),
        glm::vec4(0.5, 0.5, 0.5, 1.f),
        "%s",
        OPENSPACE_VERSION_STRING_FULL
    );

    // If a developer hasn't placed the Git command in the path, this variable will be
    // empty
    if (!std::string(OPENSPACE_GIT_COMMIT).empty()) {
        // We check OPENSPACE_GIT_COMMIT but puse OPENSPACE_GIT_FULL on purpose since
        // OPENSPACE_GIT_FULL will never be empty (always will contain at least @, but
        // checking for that is a bit brittle)
        FR::defaultRenderer().render(
            *_fontInfo,
            glm::vec2(
                fontResolution().x - commitBox.boundingBox.x - 10.f,
                versionBox.boundingBox.y + 5.f
            ),
            glm::vec4(0.5, 0.5, 0.5, 1.f),
            "%s",
            OPENSPACE_GIT_FULL
        );
    }
}

void RenderEngine::renderScreenLog() {
    if (!_showLog) {
        return;
    }

    _log->removeExpiredEntries();

    const int max = 10;
    const int categoryLength = 20;
    const int messageLength = 140;
    std::chrono::seconds fade(5);

    const std::vector<ScreenLog::LogEntry> entries = _log->entries();
    auto lastEntries =
        entries.size() > max ?
        std::make_pair(entries.rbegin(), entries.rbegin() + max) :
        std::make_pair(entries.rbegin(), entries.rend());

    size_t nr = 1;
    auto now = std::chrono::steady_clock::now();
    for (auto& it = lastEntries.first; it != lastEntries.second; ++it) {
        const ScreenLog::LogEntry* e = &(*it);

        std::chrono::duration<double> diff = now - e->timeStamp;

        float alpha = 1;
        std::chrono::duration<double> ttf = ScreenLogTimeToLive - fade;
        if (diff > ttf) {
            auto d = (diff - ttf).count();
            auto t = static_cast<float>(d) / static_cast<float>(fade.count());
            float p = 0.8f - t;
            alpha = (p <= 0.f) ? 0.f : pow(p, 0.4f);
        }

        // Since all log entries are ordered, once one exceeds alpha, all have
        if (alpha <= 0.0) {
            break;
        }

        const std::string lvl = "(" + ghoul::logging::stringFromLevel(e->level) + ")";
        const std::string& message = e->message.substr(0, messageLength);
        nr += std::count(message.begin(), message.end(), '\n');

        const glm::vec4 white(0.9f, 0.9f, 0.9f, alpha);

        RenderFont(
            *_fontLog,
            glm::vec2(10.f, _fontLog->pointSize() * nr * 2),
            white,
            "%-14s %s%s",
            e->timeString.c_str(),
            e->category.substr(0, categoryLength).c_str(),
            e->category.length() > 20 ? "..." : "");

        glm::vec4 color(glm::uninitialize);
        switch (e->level) {
            case ghoul::logging::LogLevel::Debug:
                color = glm::vec4(0.f, 1.f, 0.f, alpha);
                break;
            case ghoul::logging::LogLevel::Warning:
                color = glm::vec4(1.f, 1.f, 0.f, alpha);
                break;
            case ghoul::logging::LogLevel::Error:
                color = glm::vec4(1.f, 0.f, 0.f, alpha);
                break;
            case ghoul::logging::LogLevel::Fatal:
                color = glm::vec4(0.3f, 0.3f, 0.85f, alpha);
                break;
            default:
                color = white;
                break;
        }

        RenderFont(
            *_fontLog,
            glm::vec2(10 + 39 * _fontLog->pointSize(), _fontLog->pointSize() * nr * 2),
            color,
            "%s",
            lvl.c_str()
        );

        RenderFont(*_fontLog,
            glm::vec2(10 + 53 * _fontLog->pointSize(), _fontLog->pointSize() * nr * 2),
            white,
            "%s",
            message.c_str()
        );
        ++nr;
    }
}

std::vector<Syncable*> RenderEngine::getSyncables() {
    if (_camera) {
        return _camera->getSyncables();
    } else {
        return {};
    }
}

properties::PropertyOwner& RenderEngine::screenSpaceOwner() {
    return _screenSpaceOwner;
}

} // namespace openspace
