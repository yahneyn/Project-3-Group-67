#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/City.h"

using namespace bridges;

using namespace std;

/*
First, the user submits the importance of each preference category to them when
considering where to live. Then, the user submits their preferences for Population,
Elevation, Time Zone, Region, and State

Approach 1 – Greedy Weighted Approach:
        Matches are found that most closely match the user’s preferences according
        to the greedy algorithm. For example, if state is most important to the user,
        all results that are outside of their desired state will be disregarded.

Approach 2 – Non-Greedy Weighted Approach:
        In this approach, every city will be associated with a rank value.
        To start, these rank values will all be initialized to 0.0. Then, the algorithm
        will iterate through each city and determine whether its attributes match with
        the user’s preferences. If a compatible attribute is identified in a city, a
        weighted score will be added to it’s rank value.
*/

class UIElement {
public:
    int populationMax, elevationMax, stateNum;
    string timeZone, state;
    vector<string> timeZoneMatches;
    unordered_map<string, string> userResponses;

    string cityGraphic = {"                       .|\n"
                          "                       | |\n"
                          "                       |'|            ._____\n"
                          "               ___    |  |            |.   |' .---\"|\n"
                          "       _    .-'   '-. |  |     .--'|  ||   | _|    |\n"
                          "    .-'|  _.|  |    ||   '-__  |   |  |    ||      |\n"
                          "    |' | |.    |    ||       | |   |  |    ||      |\n"
                          " ___|  '-'     '    \"\"       '-'   '-.'    '`      |____\n"
                          "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"};

    vector<string> us_states_abbreviated = {
            "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
    };

    vector<string> us_state_names = {
            "Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware", "Florida", "Georgia",
            "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts",
            "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
            "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island",
            "South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
            "Wisconsin", "Wyoming"
    };


    vector<string> population_ranges = {
            "Less than 10,000", "10,000 - 50,000", "50,000 - 100,000",
            "100,000 - 500,000", "500,000 - 1,000,000", "More than 1,000,000"
    };

    vector<string> elevations = {"Below Sea Level", "0-500m", "500-1000m", "Above 1000m"};
    unordered_map<string, unordered_set<string>> timezoneMap = {
            {"EST", { // Eastern Standard Time
                    "America/Detroit",
                    "America/New_York",
                    "America/Indiana/Indianapolis",
                    "America/Kentucky/Louisville",
                    "America/Kentucky/Monticello",
                    "America/Indiana/Winamac",
                    "America/Indiana/Marengo",
                    "America/Indiana/Vincennes",
                    "America/Indiana/Petersburg",
                    "America/Indiana/Vevay"
            }},
            {"CST", { // Central Standard Time
                    "America/Chicago",
                    "America/Indiana/Tell_City",
                    "America/Indiana/Knox",
                    "America/Menominee",
                    "America/North_Dakota/Center",
                    "America/North_Dakota/New_Salem",
                    "America/North_Dakota/Beulah"
            }},
            {"MST", { // Mountain Standard Time
                    "America/Denver",
                    "America/Boise",
                    "America/Phoenix" // Arizona, no DST
            }},
            {"PST", { // Pacific Standard Time
                    "America/Los_Angeles",
                    "America/Sitka",
                    "America/Juneau"
            }},
            {"AKST", { // Alaska Standard Time
                    "America/Anchorage",
                    "America/Metlakatla",
                    "America/Nome"
            }},
            {"HST", { // Hawaii-Aleutian Standard Time
                    "Pacific/Honolulu"
            }}
    };

    vector<std::string> timeZones = {"EST", "CST", "MST", "PST", "AST", "HST"};
    vector<std::string> timeZonesExtended = {
            "America/Indiana/Knox",
            "America/Menominee",
            "America/Indiana/Tell_City",
            "America/Indiana/Vincennes",
            "America/North_Dakota/Center",
            "America/Metlakatla",
            "America/Kentucky/Monticello",
            "America/North_Dakota/New_Salem",
            "America/Detroit",
            "America/Sitka",
            "America/Denver",
            "America/Indiana/Petersburg",
            "America/Anchorage",
            "America/Chicago",
            "America/Los_Angeles",
            "America/Kentucky/Louisville",
            "America/Nome",
            "America/Indiana/Winamac",
            "America/New_York",
            "Pacific/Honolulu",
            "America/Indiana/Indianapolis",
            "America/Indiana/Marengo",
            "America/Juneau",
            "America/Boise",
            "America/Phoenix",
            "America/Indiana/Vevay",
            "America/North_Dakota/Beulah"
    };
    //vector<string> us_regions = {"West", "Midwest", "Southwest", "Southeast", "Northeast"};
    vector<string> questions = {
            "Preferred population size?", "Preferred elevation (in meters)?",
            "Preferred time zone?", "Preferred state?"
    };

    unordered_map<string, int> aspectsMap = {{"populationMax", 0}, {"elevationMax", 0}, {"timeZone", 0}, {"state", 0}};
    vector<string> aspects = {"populationMax", "elevationMax", "timeZone", "state"};
    vector<string> prettyAspects = {"Population", "Elevation", "Time Zone", "State"};

    void setPopulationMax(int pop) {
        if (pop == 1)
            populationMax = 10000;
        if (pop == 2)
            populationMax = 50000;
        if (pop == 3)
            populationMax = 100000;
        if (pop == 4)
            populationMax = 500000;
        if (pop == 5)
            populationMax = 1000000;
        if (pop == 6)
            populationMax = 10000000;
    }

    void setElevationMax(int ele) {
        elevationMax = ele == 1 ? 0 : ele == 2 ? 500 : ele == 3 ? 1000 : 7000;
    }

    void printPreferences() {
        cout << "Your Preferences:" << endl;
        cout << "Population Maximum: " << populationMax << endl;
        cout << "Elevation Maximum: " << elevationMax << endl;
        cout << "Time Zone: " << timeZone << endl;
        cout << "State: " << us_state_names[stateNum] << endl;
    }

    // Validate user input
    int validateSelection(int selection, int min, int max) {
        while (cin.fail() || selection < min || selection > max) {
            cin.clear(); // clear the error flag
            cin.ignore(1000, '\n'); // discard invalid input up to 1000 characters
            cout << "Invalid selection. Please enter a number between " << min << " and " << max << ": " << endl;
            cin >> selection; // re-prompt for input
        }
        return selection;
    }

    bool isInteger(const std::string &str) {
        if (str.empty()) {
            return false;
        }

        // Check for optional leading sign
        size_t start = 0;
        if (str[0] == '+' || str[0] == '-') {
            start = 1;
        }

        // Check if all remaining characters are digits
        return std::all_of(str.begin() + start, str.end(), ::isdigit);
    }

    void loadUserResponseMap(){
        userResponses["populationMax"] = to_string(populationMax);
        userResponses["elevationMax"] = to_string(elevationMax);
        userResponses["timeZone"] = timeZone;
        userResponses["state"] = state;
    }

    void rankAspects() {
        cout << "\nRank the following aspects from 1 (most important) to 4 (least important): " << endl;
        unordered_map<string, int> temp;  // To store the aspect and its rank
        unordered_set<int> rankSet;  // To track the unique ranks
        string userInput;

        for (int i = 0; i < aspects.size(); i++) {
            cout << i + 1 << ". " << prettyAspects[i] << ": " << endl;
            while (true) {
                cin >> userInput;
                if(isInteger(userInput)){
                    // Check if input is valid and an integer between 1 and 5
                    if (cin.fail() || stoi(userInput) < 1 || stoi(userInput) > 4 || userInput.size() != 1 || rankSet.find(stoi(userInput)) != rankSet.end()) {
                        cin.clear();  // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                        cout << "Invalid input. Please enter a unique integer rank between 1 and 4: " << endl;
                    } else {
                        break;  // Valid input, break the loop
                    }
                }else{
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    cout << "Invalid input. Please enter a unique integer rank between 1 and 4: " << endl;
                }


            }

            rankSet.insert(stoi(userInput));
            temp[aspects[i]] = stoi(userInput);
        }

        // Display the ranking once all unique ranks are entered
        /*cout << "\nYour ranking:\n";
        for (const auto& aspect : temp) {
            cout << "  " << aspect.first << ": " << aspect.second << endl;
        }*/

        this->aspectsMap = temp;
    }
};

unordered_map<int, City> loadCityData()
{
    // US Cities Dataset

    // create bridges object
    Bridges bridges (3, "jacobbowler", "884357890438");

    DataSource ds (&bridges);

    unordered_map<string, string> city_params {
    };

    vector<City>  us_cities = ds.getUSCities(city_params);

    int id = 0;
    unordered_map<int, City> idToCityMap;
    for (auto c : us_cities)
    {

        idToCityMap[id] = c;
        id++;

        // vector order: {city, population, elevation, time zone, state}
    }

    return idToCityMap;
}

unordered_map<string, double> preferenceWeights(unordered_map<string, int>& aspectsMap)
{
    unordered_map<string, double> pWeights;

    for (auto e : aspectsMap)
        pWeights[e.first] = 0.1 * (5 - e.second);

    return pWeights;
}

vector<pair<int, double>> sortRanks(const unordered_map<int, double>& idToRank)
{
    vector<pair<int, double>> idRankVector;

    idRankVector.reserve(idToRank.size());
    for (auto e : idToRank)
    {
        idRankVector.push_back({e.first, e.second});
    }

    int n = idRankVector.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (idRankVector[j].second < idRankVector[j + 1].second)
            {
                auto temp = idRankVector[j];
                idRankVector[j] = idRankVector[j + 1];
                idRankVector[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;
    }

    return idRankVector;
}


void nonGreedyScoring(unordered_map<int, City>& cities, unordered_map<string, int>& aspectsMap, unordered_map<string, string>& userResponses, int desiredCityCount)
{
    // keys in aspectsMap: populationMax, elevationMax, timeZone, state
    /*for (auto a : aspectsMap)
    {
        cout << a.first << a.second << endl;
    }*/

    unordered_map<int, double> idToRank;


    for (auto e : cities)
    {
        idToRank[e.first] = 0.0;
    }

    for (auto idRankPair : idToRank)
    {
        double totalRank = 0.0;

        unordered_map<string, string> cityAttributes = {{"populationMax", to_string(cities[idRankPair.first].getPopulation())},
                                                        {"elevationMax", to_string(cities[idRankPair.first].getElevation())},
                                                        {"timeZone", cities[idRankPair.first].getTimeZone()},
                                                        {"state", cities[idRankPair.first].getState()}};

        unordered_map<string, double> weightMap = preferenceWeights(aspectsMap);

        for (auto attribute : cityAttributes)
        {
            if (attribute.first == "populationMax" || attribute.first == "elevationMax" )
            {
                if (attribute.first == "populationMax")
                {
                    /*
                 "Less than 10,000", "10,000 - 50,000", "50,000 - 100,000",
            "100,000 - 500,000", "500,000 - 1,000,000", "More than 1,000,000"
                 */
                    if (stoi(userResponses[attribute.first]) >= stoi(cityAttributes[attribute.first])){
                        int userTemp = stoi(userResponses[attribute.first]);
                        int cityTemp = stoi(cityAttributes[attribute.first]);
                        if(userTemp == 10000000){
                            if(cityTemp > 1000000){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 1000000){
                            if(cityTemp > 500000){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 500000){
                            if(cityTemp > 100000){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 100000){
                            if(cityTemp > 50000){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 50000){
                            if(cityTemp > 10000){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 10000){
                            if(cityTemp > 0){
                                totalRank += weightMap[attribute.first];
                            }
                        }
                    }
                }

                else
                {
                    if (stoi(userResponses[attribute.first]) >= stoi(cityAttributes[attribute.first])){
                        int userTemp = stoi(userResponses[attribute.first]);
                        int cityTemp = stoi(cityAttributes[attribute.first]);
                        if(userTemp == 7000){
                            if(cityTemp > 1000){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 1000){
                            if(cityTemp > 500){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 500){
                            if(cityTemp > 0){
                                totalRank += weightMap[attribute.first];
                            }
                        }else if(userTemp == 0){
                            if(cityTemp > -1000){
                                totalRank += weightMap[attribute.first];
                            }
                        }
                    }
                }

            }
            else if (userResponses[attribute.first] == attribute.second)
                totalRank += weightMap[attribute.first];
        }

        idToRank[idRankPair.first] = totalRank;
    }


    vector<pair<int, double>> idRankVector = sortRanks(idToRank);

    for (int i = 0; i < desiredCityCount; i++)
    {
        cout << cities[idRankVector[i].first].getCity() << ", " << cities[idRankVector[i].first].getState() << " is a " << 100*idRankVector[i].second << "% match."
        << "\n\tPopulation: " << cities[idRankVector[i].first].getPopulation()
        << "\n\tElevation: " << cities[idRankVector[i].first].getElevation()
        << "\n\tTime Zone: " << cities[idRankVector[i].first].getTimeZone() << endl;
    }
}


void greedyScoring(unordered_map<int, City>& cities, unordered_map<string, int>& aspectsMap, unordered_map<string, string>& userResponses, int desiredCityCount)
{

    // Create unordered map of cities called validCities initialized to cities
    //
    // Order the preferences from highest importance to lowest importance
    //
    // For each preference in that order
    //      For each city
    //          If the corresponding attribute does not match the user's response
    //              Remove that city from validCities
    //
    //
    //
    // Print out resulting cities in validCities


    unordered_map<int, City> validCities = cities;
    unordered_set<string> times;

    for(auto element : validCities){
        times.insert(element.second.getTimeZone());
    }

    for(auto item : times){
        cout << item << endl;
    }

    string orderedPreferences[4];
    //orderedPreferences.reserve(aspectsMap.size());
    for (auto e : aspectsMap)
    {
        orderedPreferences[e.second - 1] = e.first;
    }

    for (string aspect : orderedPreferences) {
        for (auto city : cities) {
            int elevationMaxCity;
            if (city.second.getElevation() > 1000)
                elevationMaxCity = 7000;
            else if (city.second.getElevation() > 500)
                elevationMaxCity = 1000;
            else if (city.second.getElevation() > 0)
                elevationMaxCity = 500;
            else
                elevationMaxCity = 0;


            int populationMaxCity;
            if (city.second.getPopulation() > 1000000)
                populationMaxCity = 10000000;
            else if (city.second.getPopulation() > 500000)
                populationMaxCity = 1000000;
            else if (city.second.getPopulation() > 100000)
                populationMaxCity = 500000;
            else if (city.second.getPopulation() > 50000)
                populationMaxCity = 100000;
            else if (city.second.getPopulation() > 10000)
                populationMaxCity = 50000;
            else
                populationMaxCity = 10000;

            unordered_map<string, string> cityAttributes = {{"populationMax", to_string(populationMaxCity)},
                                {"elevationMax", to_string(elevationMaxCity)},
                                {"timeZone", city.second.getTimeZone()},
                                {"state", city.second.getState()}};

            if (cityAttributes[aspect] != userResponses[aspect]) {
                validCities.erase(city.first);
            }
        }
    }

    int i = 0;

    for (auto city : validCities) {
        if (i == desiredCityCount) break;

        cout << city.second.getCity() << ", " << city.second.getState() << endl;

        i++;
    }


}

int main() {

    unordered_map<int, City> cities = loadCityData();

    UIElement matcher;
    int userSelect;

    cout << matcher.cityGraphic << endl;
    cout << "              Welcome to Dream-City Match!\n";
    cout << "Complete the following survey and we'll find your Dream-City!" << endl;
    cout << endl;

    // Population
    cout << matcher.questions[0] << endl;
    for (int i = 0; i < matcher.population_ranges.size(); i++)
        cout << i + 1 << ". " << matcher.population_ranges[i] << endl;
    cin >> userSelect;
    userSelect = matcher.validateSelection(userSelect, 1, matcher.population_ranges.size());
    matcher.setPopulationMax(userSelect);

    // Elevation
    cout << matcher.questions[1] << endl;
    for (int i = 0; i < matcher.elevations.size(); i++)
        cout << i + 1 << ". " << matcher.elevations[i] << endl;
    cin >> userSelect;
    userSelect = matcher.validateSelection(userSelect, 1, matcher.elevations.size());
    matcher.setElevationMax(userSelect);

    // Time Zone
    cout << matcher.questions[2] << endl;
    for (int i = 0; i < matcher.timeZones.size(); i++)
        cout << i + 1 << ". " << matcher.timeZones[i] << endl;
    cin >> userSelect;
    userSelect = matcher.validateSelection(userSelect, 1, matcher.timeZones.size());
    matcher.timeZone = matcher.timeZones[userSelect - 1];
    matcher.timeZoneMatches = matcher.timezoneMap[matcher.timeZone];

    // State
    cout << matcher.questions[3] << endl;
    for (int i = 0; i < matcher.us_states_abbreviated.size(); i++) {
        cout << setw(20) << left << to_string(i + 1) + ". " + matcher.us_state_names[i];
        if ((i + 1) % 5 == 0) cout << endl;
    }
    cin >> userSelect;
    userSelect = matcher.validateSelection(userSelect, 1, matcher.us_states_abbreviated.size());
    matcher.state = matcher.us_states_abbreviated[userSelect - 1];
    matcher.stateNum = userSelect-1;

    cout << endl;
    matcher.printPreferences();

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

    // Rank aspects
    matcher.rankAspects();
    matcher.loadUserResponseMap ();

    cout << "Non-Greedy Results:" << endl;
    nonGreedyScoring(cities, matcher.aspectsMap, matcher.userResponses, 25);

    cout << "Greedy Results:" << endl;
    greedyScoring(cities, matcher.aspectsMap, matcher.userResponses, 25);

}
