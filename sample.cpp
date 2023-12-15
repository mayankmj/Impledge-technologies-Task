//T.C => 0*((N+k)*M) + C , N =NO OF WRODS , K = NO OF PAIRS INSERTED IN TRIE, M = LENGHT IN STRING , C=CONSTANT OPERATIONS
// S.C => O(k + N) + C  ,SIZE OF TRIE AND MAP 

#include <bits/stdc++.h>
// #include <chrono>
using namespace std;
class Node {
public:
    char character;
    unordered_map<char, Node*> children;
    bool isTerminal;
    Node(char character = '\0', bool isTerminal = false) : character(character), isTerminal(isTerminal) {}
};
// I used Tries Data Structure, as it is type of "key-seach-treee" , in problems like string matching
// pattern , Trie can be preferred,
// else i can also recursion to iterate over each string and try to find : if any substring exist or not
// this approach will roughly takes 0(2^N) 

// I can also use DSU  , but it would be bulkier to handle character;
class Trie {
public:
    Node* root;

    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new Node(c);
            }
            curr = curr->children[c];
        }
        curr->isTerminal = true;
    }
    // if the word in contained return "TRUE" , else "FALSE"
    bool contains(std::string word) {
        Node* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return curr->isTerminal;
    }

    vector<string> getPrefixes(string word) {
        vector<string> prefixes;
        string prefix = "";
        Node* curr = root;

        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return prefixes;
            }

            curr = curr->children[c];
            prefix += c;

            if (curr->isTerminal) {
                prefixes.push_back(prefix);
            }
        }
        return prefixes;
    }
};

class ans_finder {
private:
    Trie trie;
    deque<pair<string, string>> queue;

public:
    void buildTrie(const string& filePath) {
        ifstream file(filePath);
     if (!file.is_open()) {
  cerr << "Error: File '" << filePath << "' does not exist!" <<endl;
  exit(1);
}
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                string word = line.substr(0, line.find('\n'));
                vector<string> prefixes = trie.getPrefixes(word);
                for (const auto& prefix : prefixes) {
                    int x = prefix.length();
                    pair<string,string>st;
                    st.first = word;
                    st.second = word.substr(x);
                    queue.push_back(st);
                }
                trie.insert(word);
            }
            file.close();
        } else {
            cout << "Error in opening the file!" << endl;
            exit(0);
        }
    }

    pair<string,string> findLongestCompoundWords() {
    string longest_word = "";
    int longest_length = 0;
    string second_longest = "";

    while (!queue.empty()) {
        auto front = queue.front();
        queue.pop_front();
        string word = front.first;
         string suffix = front.second;

        if (trie.contains(suffix) && word.length() > longest_length) {
            second_longest = longest_word;
            longest_word = word;
            longest_length = word.length();
        } else {
            for (const auto& prefix : trie.getPrefixes(suffix)) {
                queue.push_back({ word, suffix.substr(prefix.length()) });
            }
        }
    }
    return { longest_word, second_longest };
}

};

int main() {
    // START TIME OF THE PROGRAM
    auto start = std::chrono::steady_clock::now();
    ans_finder ans;
    ans.buildTrie("Input_01.txt");
    auto final_ans = ans.findLongestCompoundWords();
     
    cout << "Longest Compound Word: " << final_ans.first << endl;
    cout << "Second Longest Compound Word: " << final_ans.second << endl;
    // END OF PROGRAM
    auto end = std::chrono::steady_clock::now();
     std::chrono::duration<double,std::milli> elapsed_milliseconds = end - start;
    cout << "Time taken: " << elapsed_milliseconds.count() << " milliseconds" << endl;
    return 0;
}


/// Approach 
//In a file containing valid words sorted alphabetically, one word per line, 
//identifying composed words presents a unique challenge. 
//Since valid components of a composed word can appear before the word itself, 
//it can be viewed as a combination of previously read words (prefix) and a remaining suffix.
//However, a word cannot be considered composed if it contains any character that doesn't belong to any valid word in the file. 
//This "invalid character" can occur anywhere within the word, disqualifying it from being composed from valid components.
