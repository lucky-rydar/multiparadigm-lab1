#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

const string filename = "input.txt";
const int lines_per_page = 3;

struct word_count
{
    string word;
    size_t count;
};

typedef string page;
typedef vector<string> words_page;
typedef vector<words_page> book; // it contains all the pages that contains words

vector<string> ignore_words = {"in", "at", "the", "an", "for", "to", "on", "was", "were"};

int main(int argc, char** argv) {
    ifstream file(filename);
    if(!file) {
        cout << "Could not open the file" << endl;
        return 0;
    }

    stringstream ss;

    vector<page> pages;

    // read text and write pages text in list
    int line_counter = 0;
    page p = "";
while_not_eof:
    string buff;
    getline(file, buff);
    if(!buff.empty()) {
        p += buff + " ";
        line_counter++;
    }
    if(line_counter == lines_per_page) {
        line_counter = 0;
        pages.push_back(p);
        p = "";
    }

    if(!file.eof())
        goto while_not_eof;


    file.close();

    // parse every page and write it to 'book' in vector of pages
    regex word_re("\\w+");
    book book;

    auto pages_i = pages.begin();
before_loop1:
    if(pages_i != pages.end()) {
        words_page words_page;
        sregex_iterator word_re_i(pages_i->begin(), pages_i->end(), word_re);
        
    before_loop11:
        if(word_re_i != sregex_iterator()) {
            string parsed_word = word_re_i->str();
            transform(parsed_word.begin(), parsed_word.end(), parsed_word.begin(), ::tolower);
            
            words_page.push_back(parsed_word);
            word_re_i++;
            goto before_loop11;
        }
        book.push_back(words_page);
        words_page.clear();
        pages_i++;
        goto before_loop1;
    }

    // indexer is a structure with 
    map<string, vector<int>> indexer;
    int page_i = 0;
before_loop2:
    if(page_i < book.size()) {
        int word_i = 0;
    before_loop3:
        if(word_i < book[page_i].size()) {
            string word = book[page_i][word_i];
            if(indexer.find(word) == indexer.end()) {
                indexer[word] = vector<int>();
            }
            indexer[word].push_back(page_i);
            word_i++;
            goto before_loop3;
        }
        page_i++;
        goto before_loop2;
    }

    auto indexer_iter = indexer.begin();
before_loop4:
    if(indexer_iter != indexer.end()) {
        cout << indexer_iter->first << " - ";
        auto pages_numbers_iter = indexer_iter->second.begin();
    before_loop5:
        if(pages_numbers_iter != indexer_iter->second.end()) {
            cout << *pages_numbers_iter << " ";
            pages_numbers_iter++;
            goto before_loop5;
        }
        cout << endl;
        indexer_iter++;
        goto before_loop4;
    }
}
