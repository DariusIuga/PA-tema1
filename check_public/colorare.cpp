#include <bits/stdc++.h>
using namespace std;

const unsigned int MOD = 1'000'000'007;


// unsigned int get_result(const vector<char>& zones) {
//     // I'll use a greedy algorithm that calculates the number of possible combinations for k zones based on the number of combinations for k-1 zones, the type of the previous tile and the type of the current tile.

//     /* Base cases:

//     1) zones[0] == 'V' => nr_current = 3
//     2) zones[0] == 'H' => nr_current = 6

//     */
//     unsigned int nr_paintings;
//     if (zones[0] == 'V') {
//         nr_paintings = 3;
//     }
//     else {
//         nr_paintings = 6;
//     }

//     /* There are 4 general cases:

//     1) prev_zone == 'V', current_zone == 'V' => nr_current = 2 * nr_prev
//     2) prev_zone == 'V', current_zone == 'H' => nr_current = 2 * nr_prev
//     1) prev_zone == 'H', current_zone == 'V' => nr_current = 1 * nr_prev
//     1) prev_zone == 'H', current_zone == 'H' => nr_current = 3 * nr_prev

//     */
//     for (int i = 1;i < zones.size();i++) {
//         if (zones[i - 1] == 'V') {
//             nr_paintings = (nr_paintings * 2) % MOD;
//         }
//         else if (zones[i] == 'H') {
//             nr_paintings = (nr_paintings * 3) % MOD;
//         }
//     }

//     return nr_paintings;
// }

struct Group {
    int nr_zones;
    char type;
};

int fast_powers(int a, int b) {
    if (b == 0) {
        return 1;
    }
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % MOD;
        }

        a = ((long long)a * a) % MOD;
        b /= 2;
    }

    return result;
}


unsigned int get_result(const vector<Group>& groups) {
    // I'll use a greedy algorithm that calculates the number of possible combinations for k zones based on the number of combinations for k-1 zones, the type of the previous tile and the type of the current tile.

    /* Base cases:

    1) zones[0] == 'V' => nr_current = 3
    2) zones[0] == 'H' => nr_current = 6

    */
    unsigned int nr_paintings;
    if (groups[0].type == 'V') {
        nr_paintings = (3 * fast_powers(2, groups[0].nr_zones - 1)) % MOD;
    }
    else {
        nr_paintings = (6 * fast_powers(3, groups[0].nr_zones - 1)) % MOD;
    }

    /* There are 4 general cases:

    1) prev_zone == 'V', current_zone == 'V' => nr_current = 2 * nr_prev
    2) prev_zone == 'V', current_zone == 'H' => nr_current = 2 * nr_prev
    1) prev_zone == 'H', current_zone == 'V' => nr_current = 1 * nr_prev
    1) prev_zone == 'H', current_zone == 'H' => nr_current = 3 * nr_prev

    */
    for (int i = 1;i < groups.size();i++) {

        if (groups[i - 1].type == 'V') {
            nr_paintings = (nr_paintings * 2) % MOD;
            if (groups[i].type == 'V') {
                nr_paintings = (nr_paintings * fast_powers(2, groups[i].nr_zones - 1)) % MOD;
            }
            else {
                nr_paintings = (nr_paintings * fast_powers(3, groups[i].nr_zones - 1)) % MOD;
            }
        }
        else {
            if (groups[i].type == 'V') {
                nr_paintings = (nr_paintings * fast_powers(2, groups[i].nr_zones - 1)) % MOD;
            }
            else {
                nr_paintings = (nr_paintings * 3) % MOD;
                nr_paintings = (nr_paintings * fast_powers(3, groups[i].nr_zones - 1)) % MOD;
            }
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

    vector<Group> groups;

    for (int i = 0; i < nr_groups; i++) {
        Group group;
        // int nr_zones_in_group;
        // char type;
        in >> group.nr_zones >> group.type;
        groups.push_back(group);
    }
    in.close();

    // Write output
    ofstream out("colorare.out");
    // for (const Group& group : groups) {
    //     out << group.nr_zones << " " << group.type << " ";
    // }
    out << get_result(groups) << "\n";


    out.close();

    return 0;
}
