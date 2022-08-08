#pragma once

#include <string>
#include <vector>


// CLASS AND FUNCTION DECLARATIONS GO HERE

class Edge {
    std::string src;
    std::string dest;

    public:
        Edge(std::string newSrc, std::string newDest);

        std::string getSrc();
        void setSrc(std::string src);
        std::string getDest();
        void setDest(std::string dest);

        std::string toString();
        bool equals (Edge e2);
};