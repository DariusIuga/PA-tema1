#include <bits/stdc++.h>
using namespace std;

int max_vector(vector<int> vec) {
    int max = vec[0];

    for (int el : vec) {
        if (el > max) {
            max = el;
        }
    }

    return max;
}

double find_system_power(double current_choice, vector<int> power, vector<int> capacity) {
    double min = power[0] - fabs(capacity[0] - current_choice);
    for (int i = 1; i < power.size(); i++) {
        double server_power = power[i] - fabs(capacity[i] - current_choice);
        if (server_power < min) {
            min = server_power;
        }
    }

    return min;
}

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


double get_result(vector<int> power, vector<int> capacity) {
    int upper_bound = max_vector(capacity);
    return find_best(0, upper_bound, MAXFLOAT, power, capacity);
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

    // Write output
    ofstream out("servere.out");
    out << fixed << setprecision(1) << get_result(power, capacity) << "\n";
    out.close();

    return 0;
}
