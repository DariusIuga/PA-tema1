#include <fstream>

using namespace std;

#define MAX_ARR_LEN 300'000

unsigned int compress_arrays(unsigned int A[], unsigned int n, unsigned int B[], unsigned int m) {
    unsigned int length_seen_array = 0;
    unsigned int end_subarray_a = 0, end_subarray_b = 0;
    unsigned long long sum_subarray_a = A[0], sum_subarray_b = B[0];

    while (end_subarray_a < n && end_subarray_b < m)
    {
        if (sum_subarray_a < sum_subarray_b)
        {
            end_subarray_a++;
            sum_subarray_a += A[end_subarray_a];
        }
        else if (sum_subarray_a > sum_subarray_b)
        {
            end_subarray_b++;
            sum_subarray_b += B[end_subarray_b];
        }
        else
        {
            end_subarray_a++;
            end_subarray_b++;
            length_seen_array++;

            sum_subarray_a = A[end_subarray_a];
            sum_subarray_b = B[end_subarray_b];
        }
    }

    return length_seen_array;
}

int main()
{
    ios::sync_with_stdio(false);

    ifstream in("compresie.in");

    unsigned int n, m, A[MAX_ARR_LEN], B[MAX_ARR_LEN];
    unsigned long long total_sum_a, total_sum_b;

    // Get input
    in >> n;

    for (unsigned int i = 0; i < n; i++) {
        in >> A[i];
        total_sum_a += A[i];
    }

    in >> m;

    for (unsigned int i = 0; i < m; i++) {
        in >> B[i];
        total_sum_b += B[i];
    }

    ofstream out("compresie.out");

    // Write output
    if (total_sum_a != total_sum_b) {
        out << -1;
        return 0;
    }

    out << compress_arrays(A, n, B, m);

    in.close();
    out.close();
    return 0;
}

