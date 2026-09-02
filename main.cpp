#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "search.hpp"

using namespace std;

int main() {
	string dir_path = R"(D:\github\desktop-search-engine\test_data)";
	string keyword;
    vector<filesystem::path> index, keyword_results; 
    
    index = buildIndex(dir_path);
        
    while(1){
        vector<filesystem::path> same_keyword_res, prefix_keyword_res, substring_keyword_res;
        
        cout << "search> ";
        cin >> keyword;
        
        keyword = upper_to_lower(keyword);
        if(keyword == "exit")
            break;

        keyword_results = searchFiles(index, keyword);

        if(keyword_results.empty()) {
            cout << "No files found." << endl;
        }
        else {
            for(auto const& file: keyword_results) {
                cout << file << endl;
            }
        }
    }


    return 0;
}


