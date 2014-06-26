#include <set>
#include <osgUtil/Statistics>

class StatsVisitor : public osgUtil::StatsVisitor
{
public:
    StatsVisitor();
    virtual ~StatsVisitor();

    virtual void apply(osg::StateSet &ss);
    virtual void apply(osg::Drawable &drawable);
    virtual void apply(osg::Geometry &geometry);
    virtual void apply(osg::PrimitiveSet &primitive);

    virtual void reset();
    virtual void print(std::ostream &out);
    virtual void printJSON(std::ostream &out);

protected:
    unsigned _numTriangles, _numInstancedTriangles;
    unsigned _numQuads, _numInstancedQuads;
    unsigned _numFaces, _numInstancedFaces;
    unsigned _numTextures, _numInstancedTextures;
    std::set<osg::PrimitiveSet*> _primitiveSetsSet;
    std::set<osg::Texture*> _texturesSet;
};
