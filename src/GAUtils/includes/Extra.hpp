#ifndef EXTRA_CPP
#define EXTRA_CPP
#include "Population.hpp"
namespace Extra{
    void applyMutation(Tour&);
    void applyMutation(Population &pop);

    void popReset(Population &);    

    void applyRepair(Tour&);
    void applyRepair(Population&);
}
#endif