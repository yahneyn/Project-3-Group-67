#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <limits>

using namespace std;

struct UIElement {
    int populationMax, elevationMax;
    string region, timeZone, state;

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
    vector<string> us_regions = {"West", "Midwest", "Southwest", "Southeast", "Northeast"};
    vector<string> questions = {
            "Preferred population size?", "Preferred elevation (in meters)?",
            "Preferred US region?", "Preferred time zone?", "Preferred state?"
    };

    unordered_map<string, int> aspectsMap = {{"Population", 0}, {"Elevation", 0}, {"Region", 0}, {"Time Zone", 0}, {"State", 0}};
    vector<string> aspects = {"Population", "Elevation", "Region", "Time Zone", "State"};

    void setPopulationMax(int pop) {
        populationMax = pop <= 5 ? pop * 100000 : 10000000;
    }

    void setElevationMax(int ele) {
        elevationMax = ele == 1 ? 0 : ele == 2 ? 500 : ele == 3 ? 1000 : 7000;
    }

    void printPreferences() {
        cout << "Population Maximum: " << populationMax << endl;
        cout << "Elevation Maximum: " << elevationMax << endl;
        cout << "Region: " << region << endl;
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

    void rankAspects() {
        cout << "\nRank the following aspects from 1 (most important) to 5 (least important): " << endl;
        unordered_map<string, int> aspectsMap;  // To store the aspect and its rank
        unordered_set<int> rankSet;  // To track the unique ranks
        string userInput;

        for (int i = 0; i < aspects.size(); i++) {
            cout << i + 1 << ". " << aspects[i] << ": " << endl;
            while (true) {
                cin >> userInput;

                // Check if input is valid and an integer between 1 and 5
                if (cin.fail() || stoi(userInput) < 1 || stoi(userInput) > 5 || userInput.size() != 1 || rankSet.find(stoi(userInput)) != rankSet.end()) {
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    cout << "Invalid input. Please enter a unique integer rank between 1 and 5: " << endl;
                } else {
                    break;  // Valid input, break the loop
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

int main() {
    UIElement matcher;
    int userSelect;

    cout << matcher.cityGraphic << endl;
    cout << "              Welcome to Dream-City Match!\n";
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

    // Region
    cout << matcher.questions[2] << endl;
    for (int i = 0; i < matcher.us_regions.size(); i++)
        cout << i + 1 << ". " << matcher.us_regions[i] << endl;
    cin >> userSelect;
    userSelect = matcher.validateSelection(userSelect, 1, matcher.us_regions.size());
    matcher.region = matcher.us_regions[userSelect - 1];

    // Time Zone
    cout << matcher.questions[3] << endl;
    for (int i = 0; i < matcher.timeZones.size(); i++)
        cout << i + 1 << ". " << matcher.timeZones[i] << endl;
    cin >> userSelect;
    userSelect = matcher.validateSelection(userSelect, 1, matcher.timeZones.size());
    matcher.timeZone = matcher.timeZones[userSelect - 1];

    // State
    cout << matcher.questions[4] << endl;
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
}
