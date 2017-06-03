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

#include <modules/globebrowsing/globebrowsingmodule.h>

#include <modules/globebrowsing/cache/memoryawaretilecache.h>
#include <modules/globebrowsing/globes/renderableglobe.h>
#include <modules/globebrowsing/other/distanceswitch.h>
#include <modules/globebrowsing/tile/rawtiledatareader/gdalwrapper.h>
#include <modules/globebrowsing/tile/tileprovider/cachingtileprovider.h>
#include <modules/globebrowsing/tile/tileprovider/singleimageprovider.h>
#include <modules/globebrowsing/tile/tileprovider/sizereferencetileprovider.h>
#include <modules/globebrowsing/tile/tileprovider/temporaltileprovider.h>
#include <modules/globebrowsing/tile/tileprovider/texttileprovider.h>
#include <modules/globebrowsing/tile/tileprovider/tileindextileprovider.h>
#include <modules/globebrowsing/tile/tileprovider/tileprovider.h>
#include <modules/globebrowsing/tile/tileprovider/tileproviderbylevel.h>
#include <modules/globebrowsing/tile/tileprovider/tileproviderbyindex.h>
#include <modules/globebrowsing/tile/tileprovider/presentationslideprovider.h>

#include <openspace/engine/openspaceengine.h>
#include <openspace/rendering/renderable.h>
#include <openspace/util/factorymanager.h>

#include <ghoul/misc/templatefactory.h>
#include <ghoul/misc/assert.h>

#include <ghoul/systemcapabilities/generalcapabilitiescomponent.h>

namespace openspace {

const std::string GlobeBrowsingModule::name = "GlobeBrowsing";

GlobeBrowsingModule::GlobeBrowsingModule()
    : OpenSpaceModule(name)
{ }

void GlobeBrowsingModule::internalInitialize() {
    // TODO: Remove dependency on OsEng.
    // Instead, make this class implement an interface that OsEng depends on.
    // Do not try to register module callbacks if OsEng does not exist,
    // for example in the TaskRunner.

    if (!OpenSpaceEngine::isCreated()) {
        return;
    }

    using namespace globebrowsing;

    OsEng.registerModuleCallback(OpenSpaceEngine::CallbackOption::Initialize, [&] {

    _tileCache = std::make_unique<globebrowsing::cache::MemoryAwareTileCache>();
    addPropertySubOwner(*_tileCache);

#ifdef GLOBEBROWSING_USE_GDAL
        // Convert from MB to Bytes
        GdalWrapper::create(
            16ULL * 1024ULL * 1024ULL, // 16 MB
            CpuCap.installedMainMemory() * 0.25 * 1024 * 1024); // 25% of total RAM
        addPropertySubOwner(GdalWrapper::ref());
#endif // GLOBEBROWSING_USE_GDAL
    });
  
    OsEng.registerModuleCallback(OpenSpaceEngine::CallbackOption::Render, [&]{
        _tileCache->update();
    });

  
    OsEng.registerModuleCallback(OpenSpaceEngine::CallbackOption::Deinitialize, [&]{
#ifdef GLOBEBROWSING_USE_GDAL
        GdalWrapper::ref().destroy();
#endif // GLOBEBROWSING_USE_GDAL
    });

    auto fRenderable = FactoryManager::ref().factory<Renderable>();
    ghoul_assert(fRenderable, "Renderable factory was not created");
    fRenderable->registerClass<globebrowsing::RenderableGlobe>("RenderableGlobe");

    // add Tile Provider factory
    auto fTileProvider = std::make_unique<ghoul::TemplateFactory<tileprovider::TileProvider>>();

    fTileProvider->registerClass<tileprovider::CachingTileProvider>("LRUCaching");
    fTileProvider->registerClass<tileprovider::SingleImageProvider>("SingleImage");
#ifdef GLOBEBROWSING_USE_GDAL
    fTileProvider->registerClass<tileprovider::TemporalTileProvider>("Temporal");
#endif // GLOBEBROWSING_USE_GDAL

    fTileProvider->registerClass<tileprovider::TileIndexTileProvider>("TileIndex");
    fTileProvider->registerClass<tileprovider::SizeReferenceTileProvider>("SizeReference");

    // Combining Tile Providers
    fTileProvider->registerClass<tileprovider::TileProviderByLevel>("ByLevel");
    fTileProvider->registerClass<tileprovider::TileProviderByIndex>("ByIndex");
    fTileProvider->registerClass<tileprovider::PresentationSlideProvider>("PresentationSlides");
    FactoryManager::ref().addFactory(std::move(fTileProvider));
}

globebrowsing::cache::MemoryAwareTileCache* GlobeBrowsingModule::tileCache() {
    return _tileCache.get();
}

} // namespace openspace
