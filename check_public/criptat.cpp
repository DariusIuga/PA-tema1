#include <bits/stdc++.h>
using namespace std;

tuple<char, int> most_common_letter(const vector<string>& words) {
    // I need a hashmap for this
    unordered_map<char, int> letterFreq;

    for (const string& word : words) {
        // Count occurrences of each letter in the word
        for (char letter : word) {
            letterFreq[letter]++;
        }
    }

    char mostCommon = '\0';
    int maxFreq = 0;

    for (const auto& pair : letterFreq) {
        // Look at each value in the hashmap for the frequencies
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
            mostCommon = pair.first;
        }
    }

    return make_tuple(mostCommon, maxFreq);
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

int get_result(vector<string>& words, int password_length, const char letter, int frequency) {

    // Sort the vector of words in ascending order based on the frequency of 
    // the letter / length of the word. This is done in order to know
    // what words to eliminate first
    sort(words.begin(), words.end(), [letter](const string& a, const string& b) -> bool {
        double a_freq = (double)find_letter_frequency(letter, a);
        double b_freq = (double)find_letter_frequency(letter, b);

        return ((a_freq / a.length()) > (b_freq / b.length()));
        });

    // We have to eliminate words from the password until the letter that was selected becomes the dominant letter in the password
    while (frequency <= password_length / 2) {
        // Update the password by deleting the worst word from it.
        const string last_string = words.back();
        password_length -= last_string.length();
        frequency -= find_letter_frequency(letter, last_string);

        // Deleting the last word is done in O(1) time, that's why the list was sorted in descending order.
        words.pop_back();
    }

    return password_length;
}

int main() {
    std::ios::sync_with_stdio(false);

    int nr_words;
    int password_length = 0;

    // Read input
    ifstream in("criptat.in");
    in >> nr_words;

    // At first, I will add every word to the password
    vector<string> words;

    for (int i = 0; i < nr_words; i++) {
        string word;
        in >> word;
        words.push_back(word);
        password_length += word.length();
    }
    in.close();

    // Find the most common letter in all of the words and its frequency
    char chosen_letter;
    int frequency;
    // Using destructuring for tuples
    tie(chosen_letter, frequency) = most_common_letter(words);


    // Begin deleting words from the password until the letter becomes dominant
    password_length = get_result(words, password_length, chosen_letter, frequency);

    // Write output
    ofstream out("criptat.out");
    out << password_length << "\n";


    out.close();

    return 0;
}
