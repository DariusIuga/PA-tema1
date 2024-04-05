#include <bits/stdc++.h>
using namespace std;

unsigned int get_result(const vector<char>& zones) {
    // I'll use a greedy algorithm that calculates the number of possible combinations for k zones based on the number of combinations for k-1 zones, the type of the previous tile and the type of the current tile.

    /* Base cases:

    1) zones[0] == 'V' => nr_current = 3
    2) zones[0] == 'H' => nr_current = 6

    */
    const unsigned int MOD = 1'000'000'007;
    unsigned int nr_paintings;
    if (zones[0] == 'V') {
        nr_paintings = 3;
    }
    else {
        nr_paintings = 6;
    }

    /* There are 4 general cases:

    1) prev_zone == 'V', current_zone == 'V' => nr_current = 2 * nr_prev
    2) prev_zone == 'V', current_zone == 'H' => nr_current = 2 * nr_prev
    1) prev_zone == 'H', current_zone == 'V' => nr_current = 1 * nr_prev
    1) prev_zone == 'H', current_zone == 'H' => nr_current = 3 * nr_prev

    */
    for (int i = 1;i < zones.size();i++) {
        if (zones[i - 1] == 'V') {
            nr_paintings = (nr_paintings * 2) % MOD;
        }
        else if (zones[i] == 'H') {
            nr_paintings = (nr_paintings * 3) % MOD;
        }
    }

    return nr_paintings;
}


int main() {
    std::ios::sync_with_stdio(false);

    int nr_groups;

    // Read input
    ifstream in("colorare.in");
    in >> nr_groups;

    vector<char> zones;

    for (int i = 0; i < nr_groups; i++) {
        int nr_zones_in_group;
        char type;
        in >> nr_zones_in_group >> type;
        for (int j = 0; j < nr_zones_in_group; j++) {
            zones.push_back(type);
        }
    }
    in.close();

    // Write output
    ofstream out("colorare.out");
    out << get_result(zones) << "\n";


    out.close();

    return 0;
}
