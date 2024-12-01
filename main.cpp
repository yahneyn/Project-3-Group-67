#include <iostream>
#include <vector>
#include <string>
using namespace std;



class UIElement{
    int population;
    int elevation;
    string region;
    string timeZone;
    string state;

    vector<string> us_states = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware",
    "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana",
    "Maine", "Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana",
    "Nebraska", "Nevada", "New Hampshire", "New Jersey", "New Mexico", "New York", "North Carolina",
    "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina",
    "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
    "Wisconsin", "Wyoming"};

    vector<string> population_ranges = {"Less than 10,000", "10,000 - 50,000", "50,000 - 100,000", "100,000 - 500,000",
    "500,000 - 1,000,000", "More than 1,000,000"};

    vector<string> timeZones = {"EST", "CST", "MST", "PST", "AST", "HAST"};

    vector<string> cityTraits = {"Population", "Elevation", "Region", "Time Zone", "State"};

    vector<string> us_regions = {"West", "Midwest", "Southwest", "Southeast", "Northeast"};

    vector<string> questions = {"Preferred population size?",
                                "Preferred elevation?",
                                "Preferred US region?",
                                "Preferred time zone?",
                                "Preferred state?",
                                "Rank the following by importance:"};

};

int main() {
    UIElement myMatcher;
    int questionIndex = 0;

    // Welcome
    cout << "Welcome to Dream-City Match!" << endl;
    cout << myMatcher.questions[questionIndex] << endl;

}
