#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct UIElement {
    int populationMax, elevationMax;
    string region, timeZone, state;

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

    void rankAspects() {
        vector<int> ranks(5);
        cout << "\nRank the following aspects from 1 (most important) to 5 (least important):\n";
        for (int i = 0; i < aspects.size(); i++) {
            cout << i + 1 << ". " << aspects[i] << ": " << endl;
            cin >> ranks[i];
            cout << endl;
        }

        // Validate unique ranking
        sort(ranks.begin(), ranks.end());
        if (unique(ranks.begin(), ranks.end()) != ranks.end()) {
            cout << "Each aspect must have a unique rank. Please try again.\n";
            rankAspects();  // Retry if validation fails
        } else {
            cout << "\nYour ranking:\n";
            for (int i = 0; i < aspects.size(); i++) {
                cout << "  " << aspects[i] << ": Rank " << ranks[i] << endl;
            }
        }
    }
};

int main() {
    UIElement matcher;
    int userSelect;

    cout << "Welcome to Dream-City Match!\n";

    // Population
    cout << matcher.questions[0] << endl;
    for (int i = 0; i < matcher.population_ranges.size(); i++)
        cout << i + 1 << ". " << matcher.population_ranges[i] << endl;
    cin >> userSelect;
    matcher.setPopulationMax(userSelect);

    // Elevation
    cout << matcher.questions[1] << endl;
    for (int i = 0; i < matcher.elevations.size(); i++)
        cout << i + 1 << ". " << matcher.elevations[i] << endl;
    cin >> userSelect;
    matcher.setElevationMax(userSelect);

    // Region
    cout << matcher.questions[2] << endl;
    for (int i = 0; i < matcher.us_regions.size(); i++)
        cout << i + 1 << ". " << matcher.us_regions[i] << endl;
    cin >> userSelect;
    matcher.region = matcher.us_regions[userSelect - 1];

    // Time Zone
    cout << matcher.questions[3] << endl;
    for (int i = 0; i < matcher.timeZones.size(); i++)
        cout << i + 1 << ". " << matcher.timeZones[i] << endl;
    cin >> userSelect;
    matcher.timeZone = matcher.timeZones[userSelect - 1];





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


    // State
    cout << matcher.questions[4] << endl;
    for (int i = 0; i < matcher.us_states.size(); i++) {
        cout << setw(20) << left << to_string(i + 1) + ". " + matcher.us_states[i];
        if ((i + 1) % 5 == 0) cout << endl;
    }
    cin >> userSelect;
    matcher.state = matcher.us_states[userSelect - 1];

    cout << endl;
    matcher.printPreferences();

    // Rank aspects
    matcher.rankAspects();
}
