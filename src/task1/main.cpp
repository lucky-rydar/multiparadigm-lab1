#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

const string filename = "input.txt";

struct word_count
{
    string word;
    size_t count;
};

vector<string> ignore_words = {"in", "at", "the", "an", "for", "to", "on", "was", "were"};

int main(int argc, char** argv) {
    ifstream file(filename);
    if(!file) {
        cout << "Could not open the file" << endl;
        return 0;
    }

    stringstream ss;

while_not_eof:
    string buff;
    getline(file, buff);
    ss << buff << " ";
    if(!file.eof())
        goto while_not_eof;


    file.close();


    string text = ss.str();
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);

    regex re("\\w+");
    map<string, size_t> words;


    sregex_iterator i(text.begin(), text.end(), re);
while_not_end_iterator:
    if(i != sregex_iterator()) {
        string word = i->str();
        //if(/*word does not exist in ignore arr*/)
        if(std::find(ignore_words.begin(), ignore_words.end(), word) == ignore_words.end()) {
            if(words.find(word) != words.end()) {
                // found
                words[word]++;
            } else {
                words[word] = 1;
            }
        }
        i++;
        goto while_not_end_iterator;
    }
    
    vector<word_count> words_count;
    auto words_i = words.begin();
words_i_not_end:
    if(words_i != words.end()) {
        words_count.push_back({words_i->first, words_i->second});
        words_i++;
        goto words_i_not_end;
    }

    int k = 0;
while_k_not_last:
    if(k < words_count.size()) {
        int j = 0;
    while_j_not_end:
        if(j < words.size() - 1) {
            if(words_count[k].count > words_count[j].count) {
                swap(words_count[k], words_count[j]);
            }
            j++;
            goto while_j_not_end;
        }
        k++;
        goto while_k_not_last;
    }

    auto words_count_iter = words_count.begin();
words_count_iter_not_end:
    if(words_count_iter != words_count.end()) {
        cout << words_count_iter->word << " - " << words_count_iter->count << endl;
        words_count_iter++;
        goto words_count_iter_not_end;
    }
}
