#include "search.hpp"

using namespace std;

vector<filesystem::path> searchFiles(string dir_path, string keyword) {
    vector<filesystem::path> results; 
    string path;

	for(auto const& dir_entry: filesystem::recursive_directory_iterator{dir_path}) {
        if(dir_entry.is_regular_file()) {
            path = dir_entry.path().filename().string();
            if(path.find(keyword) != string::npos)
                results.push_back(dir_entry.path());
        }
    }

    return results;
}


