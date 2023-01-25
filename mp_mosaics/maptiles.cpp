/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    std::map<Point<3>, TileImage*> Tree;
    std::vector<Point<3>> Color;
    for(auto it = theTiles.begin(); it != theTiles.end();++it){
        Tree[convertToXYZ((*it).getAverageColor())] = &(*it);
        Color.push_back(convertToXYZ((*it).getAverageColor()));
    }
    KDTree<3> colorTree(Color);
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    for(int x = 0; x < canvas->getRows();x++){
        for(int y =0; y < canvas->getColumns();y++){
            canvas->setTile(x,y,Tree[colorTree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(x,y)))]);
        }
    }

    return canvas;
}

