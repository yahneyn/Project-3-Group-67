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

struct UIElement {
    int populationMax, elevationMax;
    string timeZone, state;
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

    vector<string> us_states = {
            "Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware",
            "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana",
            "Maine", "Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana",
            "Nebraska", "Nevada", "New Hampshire", "New Jersey", "New Mexico", "New York", "North Carolina",
            "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina",
            "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
            "Wisconsin", "Wyoming"
    };

    vector<string> population_ranges = {
            "Less than 10,000", "10,000 - 50,000", "50,000 - 100,000",
            "100,000 - 500,000", "500,000 - 1,000,000", "More than 1,000,000"
    };

    vector<string> elevations = {"Below Sea Level", "0-500m", "500-1000m", "Above 1000m"};
    vector<string> timeZones = {"EST", "CST", "MST", "PST", "AST", "HAST"};
    //vector<string> us_regions = {"West", "Midwest", "Southwest", "Southeast", "Northeast"};
    vector<string> questions = {
            "Preferred population size?", "Preferred elevation (in meters)?",
            "Preferred time zone?", "Preferred state?"
    };

    unordered_map<string, int> aspectsMap = {{"populationMax", 0}, {"elevationMax", 0}, {"timeZone", 0}, {"state", 0}};
    vector<string> aspects = {"Population", "Elevation", "Time Zone", "State"};

    void setPopulationMax(int pop) {
        populationMax = pop <= 5 ? pop * 100000 : 10000000;
    }

    void setElevationMax(int ele) {
        elevationMax = ele == 1 ? 0 : ele == 2 ? 500 : ele == 3 ? 1000 : 7000;
    }

    void printPreferences() {
        cout << "Results:" << endl;
        cout << "Population Maximum: " << populationMax << endl;
        cout << "Elevation Maximum: " << elevationMax << endl;
        cout << "Time Zone: " << timeZone << endl;
        cout << "State: " << state << endl;
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
        unordered_map<string, int> aspectsMap;  // To store the aspect and its rank
        unordered_set<int> rankSet;  // To track the unique ranks
        string userInput;

        for (int i = 0; i < aspects.size(); i++) {
            cout << i + 1 << ". " << aspects[i] << ": " << endl;
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
            aspectsMap[aspects[i]] = stoi(userInput);
        }

        // Display the ranking once all unique ranks are entered
        cout << "\nYour ranking:\n";
        for (const auto& aspect : aspectsMap) {
            cout << "  " << aspect.first << ": " << aspect.second << endl;
        }
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

    // State
    cout << matcher.questions[3] << endl;
    for (int i = 0; i < matcher.us_states.size(); i++) {
        cout << setw(20) << left << to_string(i + 1) + ". " + matcher.us_states[i];
        if ((i + 1) % 5 == 0) cout << endl;
    }
    cin >> userSelect;
    userSelect = matcher.validateSelection(userSelect, 1, matcher.us_states.size());
    matcher.state = matcher.us_states[userSelect - 1];

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
}
