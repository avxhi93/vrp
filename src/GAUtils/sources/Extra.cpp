#include "Extra.hpp"
#include "Configs.hpp"
#include "InitialPop.hpp"
#include "Kmeans.hpp"
#include "Mutation.hpp"
#include "Opt.hpp"
#include "TourRepairer.hpp"
#include "Trim.hpp"

/* void Extra::popReset(Population &pop){ // OLD
    unsigned size{(unsigned) pop.getPop().size()};
    unsigned nToKeep{(unsigned)std::round(((size)*ResetConfigs::nBestToKeep)/100)};
    // std::cout << "NToKeep " << nToKeep << std::endl;  

    Population aux;
    aux.getPop().insert(aux.getPop().end(), pop.getPop().begin(), pop.getPop().begin()+nToKeep);

    for(unsigned i{nToKeep}; i<size; i++) {
        Tour t{InitialPop::tourGen()};
        // std::cout << "==================== Gerado:======================== \n" << t << std::endl;
        applyRepair(t);
        // std::cout << "========================Reparado========================\n" << t << std::endl;
        applyOptInSubs(t);
        // std::cout << "========================OPT========================\n" << t << std::endl;
        aux.addNewTour(t);
    }
    pop = aux;
    pop.sortPop();
}*/

void Extra::popReset(Population& pop)
{ // NEW
    unsigned size{ (unsigned)pop.getPop().size() };
    unsigned nToKeep{ (unsigned)std::round(((size)*ResetConfigs::nBestToKeep) / 100) };

    Population aux;
    aux.getPop().insert(aux.getPop().end(), pop.getPop().begin(), pop.getPop().begin() + nToKeep);
    for (unsigned i{ nToKeep }; i < size; i++) {
        Tour t{ InitialPop::tourGen() };
        //std::cout << "==================== Gerado:======================== \n" << t << std::endl;
        int countRepair{ 0 };
        while (!t.isValid() && countRepair != 5) {
            //std::cout << "REPARA A MERDA"<<std::endl;
            applyRepair(t);
            countRepair++;
        }
        //std::cout << "========================Reparado========================\n" << t << std::endl;
        applyOptInSubs(t);
        //std::cout << "========================OPT========================\n" << t << std::endl;
        aux.addNewTour(t);
    }
    pop = aux;
    pop.sortPop();
}

void Extra::fillPop(Population& pop)
{
    unsigned size{ pop.getPop().size() };
    //unsigned nToKeep{ (unsigned)std::round(((size)*ResetConfigs::nBestToKeep) / 100) };
    Population newPop;
    newPop = InitialPop::InitialPopAdvanced(Configs::popSize - size);
    newPop.getPop().insert(newPop.getPop().end(), pop.getPop().begin(), pop.getPop().end());
    newPop.sortPop();
    pop = newPop;
}

void Extra::applyMutation(Population& pop)
{
    double Rate = (double)MutationCtrl::mutationRate / (double)100;
    //std::cout<<"Rate::"<<Rate<<std::endl;
    unsigned numIndiv = pop.getPop().size() * Rate;
    //std::cout<<"Num Indiv Mutate: "<<numIndiv<<std::endl;
    if (MutationCtrl::applyWorst) {
        for (unsigned i = pop.getPop().size() - 1; i > (pop.getPop().size() - (numIndiv)); i--) {
            applyMutation(pop.getPop()[i]);
        }
    } else {
        for (unsigned i = 0; i < numIndiv; i++) {
            applyMutation(pop.getPop()[i]);
        }
    }
    pop.sortPop();
}

void Extra::applyMutation(Tour& tour)
{
    tour = Tour(Mutation::evaluateMutation(tour.getRoute()));
}

void Extra::applyRepair(Population& pop)
{
    for (unsigned i = 0; i < pop.getPop().size(); i++) {
        applyRepair(pop.getPop()[i]);
    }
    pop.sortPop();
}
void Extra::applyRepair(Tour& tour)
{
    Tour aux = tour;
    auto sizeB = tour.getRoute().size();
    tour = TourRepairer::repairTourV3(tour);
    auto sizeA = tour.getRoute().size();
    if(sizeB!=sizeA){
        std::cout<<aux<<std::endl;
        std::cout<<"AAAAAAAAAAAAAAAAAAAAA quebrou AAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
        std::cout<<tour<<std::endl;
        exit(-2);
    }
}

void Extra::applyRepairV4(Population& pop)
{
    for (unsigned i = 0; i < pop.getPop().size(); i++) {
        applyRepairV4(pop.getPop()[i]);
    }
    pop.sortPop();
}
void Extra::applyRepairV4(Tour& tour)
{
    // auto sizeB = tour.getRoute().size();
    tour = TourRepairer::repairTourV4(tour);
    // auto sizeA = tour.getRoute().size();
    // if(sizeB!=sizeA){
    //     std::cout<<"AAAAAAAAAAAAAAAAAAAAA quebrou AAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
    // }
}
void Extra::applyCombined(Tour& tour)
{
    applyRepair(tour);
    applyRepairV4(tour);
}
void Extra::applyCombined(Population& pop)
{
    applyRepair(pop);
    applyRepairV4(pop);
}

void Extra::applyTrim(Tour& tour)
{
    tour = Trim::applyTrim(tour);
}

void Extra::applyTrim(Population& pop)
{
    for (unsigned i = 0; i < pop.getPop().size(); i++) {
        applyTrim(pop.getPop()[i]);
    }
    pop.sortPop();
}

void Extra::applyOptInPop(Population& pop)
{
    for (Tour& t : pop.getPop()) {
        applyOptInSubs(t);
    }
    pop.sortPop();
}
void Extra::applyOptInSubs(Tour& t)
{
    // Execute the 2-opt in each subtour, do not destroy limit of charge and improve the customer distribution
    int depotId{ Globals::customerMap.getDepotId() };
    int empty{ t.getEmptySubtoursNumber() };
    vector<vector<int>> subTours{ t.explodeSubTours() };
    vector<int> newT;
    newT.reserve(t.getRoute().size());

    // Run optimize and save results
    for (vector<int>& subT : subTours) {
        subT = Opt::optimize(subT);
    }

    // Insert the new subtours in a New tour
    for (vector<int> subT : subTours) {
        newT.push_back(depotId);
        newT.insert(newT.end(), subT.begin(), subT.end());
    }

    // Load the new tour with empty routes of old tour
    while (empty > 0) {
        newT.push_back(depotId);
        empty--;
    }

    t = Tour(newT);
}
//Implementar aqui como será a nova heuristica
void Extra::applyKmeans(Tour& t)
{
    t = Kmeans::run(t);
}

void Extra::applyKmeans(Population& p)
{
    for (Tour& t : p.getPop()) {
        applyKmeans(t);
    }
    p.sortPop();
}