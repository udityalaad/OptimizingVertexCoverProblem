#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "edge.hpp"


Edge :: Edge (std::string newSrc, std::string newDest) {
    src = newSrc;
    dest = newDest;
}

std::string Edge :: getSrc()  {
    return src;
}

void Edge :: setSrc(std::string newSrc)  {
    src = newSrc;
}


std::string Edge :: getDest()  {
    return dest;
}

void Edge :: setDest(std::string newDest)  {
    dest = newDest;
}

std::string Edge :: toString() {
    return "<" + src + "," + dest + ">";
}

bool Edge :: equals (Edge e2) {
    return (src == e2.getSrc()  &&  dest == e2.getDest());
}