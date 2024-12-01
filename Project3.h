#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;


void weightedScoring(map<int, vector<string>> cityList, vector<string> preferences, vector<int> weights) {
    //weight certain aspects more than others
    map<int, vector<string>> highScore;
    for(auto iter = cityList.begin(); iter != cityList.end(); iter++) {
        int sum = 0;
        for (int i = 0; i < iter->second.size(); i++) {
            if (iter->second[i] == preferences[i]) {
                sum += (6-weights[i]);
            }
        }
        highScore[sum].push_back(iter->first);
    }
    auto iter = highScore.end() - 1;
    int val = 20;
    while(val > 0) {
        for(int i = 0; i < iter->second.size(); i++) {
            cout << iter->second[i] << ": " << iter->first << endl;
            val--;
        }
        iter--;
    }
}
