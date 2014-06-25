#include <iomanip>
#include <iostream>
#include "StatsVisitor.h"

#include <osg/Geode>
#include <osg/Geometry>

StatsVisitor::StatsVisitor()
{
    reset();
}

StatsVisitor::~StatsVisitor()
{
}

void StatsVisitor::reset()
{
    _numTriangles = _numInstancedTriangles = 0;
    _numQuads = _numInstancedQuads = 0;
    _numFaces = _numInstancedFaces = 0;
    _primitiveSetsSet.clear();

    osgUtil::StatsVisitor::reset();
}

void StatsVisitor::apply(osg::Drawable &drawable)
{
    osg::Geometry* geometry = drawable.asGeometry();

    if (geometry)
        apply(*geometry);

    osgUtil::StatsVisitor::apply(drawable);
}

void StatsVisitor::apply(osg::Geometry &geometry)
{
    size_t primitiveSetCount = geometry.getNumPrimitiveSets();
    for (unsigned int j = 0; j < primitiveSetCount; j++) {
        osg::PrimitiveSet* primitive = geometry.getPrimitiveSet(j);

        if (primitive)
            apply(*primitive);
    }
}

void StatsVisitor::apply(osg::PrimitiveSet &primitive)
{
    unsigned triangles = 0,
             quads = 0;
    switch (primitive.getMode()) {
    case osg::PrimitiveSet::TRIANGLES:
        triangles = primitive.getNumIndices();
        break;
    case osg::PrimitiveSet::QUADS:
        quads = primitive.getNumIndices() * 2;
        break;
    case osg::PrimitiveSet::TRIANGLE_STRIP:
    case osg::PrimitiveSet::TRIANGLE_FAN:
        triangles = primitive.getNumIndices() - 2;
        break;
    case osg::PrimitiveSet::QUAD_STRIP:
        quads = primitive.getNumIndices() / 2 - 1;
        break;
    }

    if (_primitiveSetsSet.count(&primitive) == 0) {
        _primitiveSetsSet.insert(&primitive);
        _numTriangles += triangles;
        _numQuads += quads;
        _numFaces += triangles + quads;
    }
    _numInstancedTriangles += triangles;
    _numInstancedQuads += quads;
    _numInstancedFaces += triangles + quads;
}

void StatsVisitor::print(std::ostream &out)
{
    osgUtil::StatsVisitor::print(out);

    out << std::setw(12) << "Triangles  " << std::setw(10) << _numTriangles << std::setw(10) << _numInstancedTriangles << std::endl;
    out << std::setw(12) << "Quads      " << std::setw(10) << _numQuads << std::setw(10) << _numInstancedQuads << std::endl;
    out << std::setw(12) << "Faces      " << std::setw(10) << _numFaces << std::setw(10) << _numInstancedFaces << std::endl;
}
