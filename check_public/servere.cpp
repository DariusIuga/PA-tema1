#include <bits/stdc++.h>
using namespace std;


// Calculates the computational power of the system for a given current value
double find_system_power(double current_choice, vector<int> power, vector<int> capacity) {
    // The power of the whole system is equal to the minimum power of any server
    double min = power[0] - fabs(capacity[0] - current_choice);
    for (int i = 1; i < power.size(); i++) {
        double server_power = power[i] - fabs(capacity[i] - current_choice);
        if (server_power < min) {
            min = server_power;
        }
    }

    return min;
}

// The problem is solved by finding the maximum of the function 
// find_system_power in the interval [lo, hi] using a divide et impera method
double find_best(double lo, double hi, double old_result, vector<int> power, vector<int> capacity) {
    double mid = (lo + hi) / 2;
    double lo_power = find_system_power(lo, power, capacity);
    double mid_power = find_system_power(mid, power, capacity);
    double hi_power = find_system_power(hi, power, capacity);


    if ((old_result != mid_power) && (fabs(old_result - mid_power) < 0.001)) {
        return mid_power;
    }

    old_result = mid_power;

    if (hi_power >= lo_power) {
        return find_best(mid, hi, old_result, power, capacity);
    }
    else {
        return find_best(lo, mid, old_result, power, capacity);
    }
}

int main() {
    ios::sync_with_stdio(false);

    int nr_servers;
    vector<int> power;
    vector<int> capacity;

    // Read input
    ifstream in("servere.in");
    in >> nr_servers;

    for (int i = 0; i < nr_servers; i++) {
        int e;
        in >> e;
        power.push_back(e);
    }
    for (int i = 0; i < nr_servers; i++) {
        int e;
        in >> e;
        capacity.push_back(e);
    }
    in.close();

    int lower_bound = capacity[0], upper_bound = capacity[0];

    for (int el : capacity) {
        if (el > upper_bound) {
            upper_bound = el;
        }
        if (el < lower_bound) {
            lower_bound = el;
        }
    }
    double best_current = find_best(lower_bound, upper_bound, MAXFLOAT, power, capacity);

    // Write output
    ofstream out("servere.out");
    out << fixed << setprecision(1) << best_current << "\n";
    out.close();

    return 0;
}
