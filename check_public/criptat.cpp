#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> countLetters(const vector<string>& strings) {
    unordered_map<char, int> letterCount;

    for (const string& str : strings) {
        for (char c : str) {
            // Increment count for the letter
            letterCount[c]++;
        }
    }

    return letterCount;
}

int find_letter_frequency(const char my_ch, const string& str) {
    int freq = 0;
    for (auto& ch : str) {
        if (my_ch == ch) {
            freq++;
        }
    }

    return freq;
}

int get_password_length(vector<string> words, int password_length, const char letter, int frequency) {

    // Sort the vector of words in ascending order based on the frequency of the letter / length of the word. This is
    // done in order to know what words to eliminate first
    sort(words.begin(), words.end(), [letter](const string& a, const string& b) -> bool {
        double a_freq = (double)find_letter_frequency(letter, a);
        double b_freq = (double)find_letter_frequency(letter, b);

        double a_ratio = a_freq / a.length();
        double b_ratio = b_freq / b.length();
        return a_ratio > b_ratio;
        });

    // We have to eliminate words from the password until the letter that was selected becomes the dominant letter in
    // the password
    while (frequency <= password_length / 2) {
        // Update the password by deleting the worst word from it.
        if (password_length == 0) {
            // I can't write a password using this letter as the dominant one
            return 0;
        }
        const string last_string = words.back();
        password_length -= last_string.length();
        frequency -= find_letter_frequency(letter, last_string);

        // Deleting the last word is done in O(1) time, that's why the list was sorted in descending order.
        words.pop_back();
    }

    return password_length;
}

int main() {
    ios::sync_with_stdio(false);

    int nr_words;
    int total_length = 0;

    // Read input
    ifstream in("criptat.in");
    in >> nr_words;

    // At first, I will add every word to the password
    vector<string> words;

    for (int i = 0; i < nr_words; i++) {
        string word;
        in >> word;
        words.push_back(word);
        total_length += word.length();
    }
    in.close();

    // Get a hashmap of all letters that occur in the password and their frequencies
    unordered_map<char, int> letterCount = countLetters(words);
    int max_password_length = 0;

    // For every letter, delete words from the password until it becomes the dominant letter
    for (const auto& pair : letterCount) {
        int password_length = get_password_length(words, total_length, pair.first, pair.second);
        // Get the longest password with a given dominant letter
        if (password_length > max_password_length) {
            max_password_length = password_length;
        }
    }

    // Write output
    ofstream out("criptat.out");
    out << max_password_length << "\n";


    out.close();

    return 0;
}
