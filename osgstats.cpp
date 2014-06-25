#include <iostream>
#include <osgDB/ReadFile>
#include <string>

#include "StatsVisitor.h"

int main(int argc, char* argv[])
{
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [options] file.osg" << std::endl
                  << "Options:" << std::endl
                  << "  --json: outputs as JSON format" << std::endl;
        return 1;
    }

    bool asJSON = false;
    for (unsigned i = 1; i < argc - 1; i++) {
        if (std::string(argv[i]) == "--json")
            asJSON = true;
    }

    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(argv[argc - 1]);
    if (!node) {
        std::cerr << "Couldn't read node file" << std::endl;
        return 1;
    }

    StatsVisitor stats;
    node->accept(stats);
    stats.totalUpStats();
    if (asJSON)
        stats.printJSON(std::cout);
    else
        stats.print(std::cout);

    return 0;
}
