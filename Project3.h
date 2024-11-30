#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;


string weightedScoring(map<int, vector<string>> cityList, string state) {
  //weight certain aspects more than others
  pair<string, int> highScore = makepair(name, 0);
  for(auto iter = cityList.begin(); iter != cityList.end(); iter++) {
    int sum = 0;
    for(int i = 0; i < iter.second.size(); i++ {
      //weight * aspect
      if(isdigit(iter.second[i][0]) {
        sum += stoi(iter.second[i]);
      }
      else{
        if(iter.second[i] == state) {
          sum ++;
        }
      }
    }
    if(sum > highScore.second) {
      highScore.first = iter.first;
      highScore.second = sum;
    }
  }
  return highScore.first;
}
