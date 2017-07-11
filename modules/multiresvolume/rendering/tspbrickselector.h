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

#ifndef __OPENSPACE_MODULE_MULTIRESVOLUME___TSPBRICKSELECTOR___H__
#define __OPENSPACE_MODULE_MULTIRESVOLUME___TSPBRICKSELECTOR___H__

#include <vector>
#include <modules/multiresvolume/rendering/tsp.h>
#include <modules/multiresvolume/rendering/brickselector.h>
#include <modules/multiresvolume/rendering/brickselection.h>
#include <modules/multiresvolume/rendering/brickcover.h>

namespace openspace {

class TransferFunction;

class TSPBrickSelector : public BrickSelector {
public:
    TSPBrickSelector();
    TSPBrickSelector(TSP* tsp);
    TSPBrickSelector(TSP* tsp, int memoryBudget, int streamingBudget);
    TSPBrickSelector(TSP* tsp, TransferFunction* tf, int memoryBudget, int streamingBudget);
    virtual ~TSPBrickSelector();

    virtual int getTimeStepCount();
    virtual int getBrickCount();

protected:
    TSP* _tsp;
    TransferFunction* _transferFunction;

    int linearCoords(int x, int y, int z);
    void writeSelection(BrickSelection brickSelection, std::vector<int>& bricks);
    std::vector<float> getTfGradients();
};

} // namespace openspace

#endif // __OPENSPACE_MODULE_MULTIRESVOLUME___TSPBRICKSELECTOR___H__