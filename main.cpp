#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "search.hpp"

using namespace std;

int main() {
	string dir_path = R"(D:\github\desktop-search-engine\test_data)";
	string keyword;
    vector<filesystem::path> results; 

    cout << "search> ";
    cin >> keyword;
    
    results = searchFiles(dir_path, keyword);
    
    if(results.empty()) {
       cout << "No files found." << endl;
    }
    else {
        for(auto const& res: results){
            cout << res << endl;
        }
    }


    return 0;
}


