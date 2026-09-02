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
        cout << "search> ";
        cin >> keyword;

        if(keyword == "exit")
            break;

        keyword_results = searchFiles(index, keyword);

        if(keyword_results.empty()) {
            cout << "No files found." << endl;
        }
        else {
            for(auto const& res: keyword_results){
                cout << res << endl;
            }
        }
    }


    return 0;
}


