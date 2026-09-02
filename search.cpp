#include "search.hpp"
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

vector<filesystem::path> buildIndex(string dir_path) {
    vector<filesystem::path> index;

	for(auto const& dir_entry: filesystem::recursive_directory_iterator{dir_path}) {
        if(dir_entry.is_regular_file()) {
            index.push_back(dir_entry.path());
        }
    }

    return index;
}

vector<filesystem::path> searchFiles(const vector<filesystem::path>& results, string keyword) {
    vector<filesystem::path> keyword_files;
    string path;

    for(auto const& file: results){
        path = file.filename().string();
        if(path.find(keyword) != string::npos)
            keyword_files.push_back(file);
    } 

    return keyword_files;
}
