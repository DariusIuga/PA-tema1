#include <stdlib.h>

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

#define MAX_ARR_LEN 10'000

const double apply_pair_discount(const unsigned int first,
                                 const unsigned int second) {
    return (double)min(first, second) / 2 + max(first, second);
}

const unsigned int apply_triple_discount(const unsigned int first,
                                         const unsigned int second,
                                         const unsigned int third) {
    const unsigned int minimum = min(min(first, second), third);

    if (minimum == first) {
        return second + third;
    } else if (minimum == second) {
        return first + third;
    } else {
        return first + second;
    }
}

double find_min_price(const unsigned int products[],
                      const unsigned int nr_products) {
    // Subproblem: dp[i] -> The minimum price for buying the first i+1 products
    // from the array Goal: find dp[nr_products - 1]

    double dp[MAX_ARR_LEN];

    // Base cases: dp[0], dp[1], dp[2]
    dp[0] = products[0];
    dp[1] = apply_pair_discount(products[0], products[1]);

    // dp[2] has 3 subcases, I need to find the minimum of all 3
    const double product_and_pair =
        products[0] + apply_pair_discount(products[1], products[2]);
    const double pair_and_product =
        apply_pair_discount(products[0], products[1]) + products[2];
    const double first_triple =
        apply_triple_discount(products[0], products[1], products[2]);

    dp[2] = min(min(product_and_pair, pair_and_product), first_triple);

    // General case: dp [i], i = 3..nr_products - 1 It is found by calculating
    // the result of dp[i-1], dp[i-2] and dp[i - 3] + the last product price,
    // last pair price, and last triple price respectively, and finding the
    // minimum of all 3.
    double prev_and_one_product, prev_and_pair, prev_and_triple;

    for (unsigned int i = 3; i < nr_products; i++) {
        prev_and_one_product = dp[i - 1] + products[i];
        prev_and_pair =
            dp[i - 2] + apply_pair_discount(products[i - 1], products[i]);
        prev_and_triple =
            dp[i - 3] + apply_triple_discount(products[i - 2], products[i - 1],
                                              products[i]);

        // Now get the minimum from all of these 3 subcases
        dp[i] = min(min(prev_and_one_product, prev_and_pair), prev_and_triple);
    }

    // The last element in dp contains the solution for the entire problem
    return dp[nr_products - 1];
}

int main() {
    ios::sync_with_stdio(false);

    ifstream in("oferta.in");
    ofstream out("oferta.out");

    unsigned int nr_products, K, products[MAX_ARR_LEN], price;

    // Get input
    in >> nr_products >> K;

    for (unsigned int i = 0; i < nr_products; i++) {
        in >> products[i];
    }

    // Write output
    if (K > 1) {
        out << fixed << setprecision(1) << -1;
    } else {
        out << fixed << setprecision(1)
            << find_min_price(products, nr_products);
    }

    in.close();
    out.close();
    return 0;
}
