#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <limits>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/City.h"

using namespace bridges;

using namespace std;


//void weightedScoring(map<string, vector<string>> cityList, vector<string> preferences, vector<int> weights) {
//    //weight certain aspects more than others
//    map<int, vector<string>> highScore;
//    for(auto iter = cityList.begin(); iter != cityList.end(); iter++) {
//        int sum = 0;
//        for (int i = 0; i < iter->second.size(); i++) {
//            if (iter->second[i] == preferences[i]) {
//                sum += (6-weights[i]);
//            }
//        }
//        highScore[sum].push_back(iter->first);
//    }
//    auto iter = highScore.end() - 1;
//    int val = 20;
//    while(val > 0) {
//        for(int i = 0; i < iter->second.size(); i++) {
//            cout << iter->second[i] << ": " << iter->first << endl;
//            val--;
//        }
//        iter--;
//    }
//}

/* Rank algorithm pseudocode
 *
 * create unordered map idRankMap of city_id (string) -> rank (double)
 *
 * place all city IDs in map and initialize ranks to 0.0
 * for each city ID in idRankMap
     * total_rank = 0
     * for each city attribute under city_id
     *    if user response contains attribute
     *        total_rank += preference_weight
     * update rank of ID to total_rank
 *
 *
 */

unordered_map<string, double> preferenceWeights(unordered_map<string, int>& aspectsMap)
{
    unordered_map<string, double> pWeights;

    for (auto e : aspectsMap)
        pWeights[e.first] = 0.1 * (5 - e.second);

    return pWeights;
}


void nonGreedyScoring(unordered_map<int, City>& cities, unordered_map<string, int>& aspectsMap, unordered_map<string, string>& userResponses)
{
    // keys in aspectsMap: populationMax, elevationMax, timeZone, state


    unordered_map<int, double> idToRank;

    for (auto idRankPair : idToRank)
    {
        double totalRank = 0.0;


        unordered_map<string, string> cityAttributes = {{"maxPopulation", to_string(cities[idRankPair.first].getPopulation())},
                                                        {"maxElevation", to_string(cities[idRankPair.first].getElevation())},
                                                        {"timeZone", cities[idRankPair.first].getTimeZone()},
                                                        {"state", cities[idRankPair.first].getState()}};

        unordered_map<string, double> weightMap = preferenceWeights(aspectsMap);

        for (auto attribute : cityAttributes)
        {
            if (attribute.first == "maxPopulation" || attribute.first == "maxElevation" )
            {
                if (stoi(userResponses[attribute.first]) >= stoi(cityAttributes[attribute.first])){
                    totalRank += double(weightMap[attribute.first]);
                }
            }
            else if (userResponses[attribute.first] == attribute.second)
                totalRank += double(weightMap[attribute.first]);
        }

        idToRank[idRankPair.first] = totalRank;
    }



    for (int i = 0; i < 50; i++)
    {
        cout << cities[i].getCity() << ", " << cities[i].getState() << " has rank " << idToRank[i] << endl;
    }

}