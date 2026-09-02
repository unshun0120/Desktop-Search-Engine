#include "search.hpp"
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

// record the files which we found
vector<filesystem::path> buildIndex(string dir_path) {
    vector<filesystem::path> index;

	for(auto const& dir_entry: filesystem::recursive_directory_iterator{dir_path}) {
        if(dir_entry.is_regular_file()) {
            index.push_back(dir_entry.path());
        }
    }

    return index;
}

// take the files which match the keyword
vector<filesystem::path> searchFiles(const vector<filesystem::path>& index, string keyword) {
    vector<filesystem::path> keyword_files, same_keyword_res, prefix_keyword_res, substring_keyword_res;
    string path;

    // upper to lower letter
    keyword = upper_to_lower(keyword);

    for(auto const& file: index){
        path = file.filename().string();

        // upper to lower letter
        path = upper_to_lower(path);

        if(path.find(keyword) != string::npos) {
            keyword_files.push_back(file);
        } 
    }

    // same
    for(auto const& res: keyword_files) {
        string stem = res.stem().string();
            // upper to lower letter
            stem = upper_to_lower(stem);

            if(stem.compare(keyword) == 0) {
                same_keyword_res.push_back(res);
            }
        }      

    //lower same
    for(auto const& res: keyword_files) {
        string stem = res.stem().string();
        // upper to lower letter                
        stem = upper_to_lower(stem);

        if(stem.starts_with(keyword) &&
            stem.compare(keyword) != 0) {
                prefix_keyword_res.push_back(res);
            }
    } 
            
    //appear in the middle
    for(auto const& res: keyword_files) {
        string stem = res.stem().string();
        // upper to lower letter              
        stem = upper_to_lower(stem);
            
        if(stem.find(keyword) != string::npos &&
            stem.compare(keyword) != 0 && 
            !stem.starts_with(keyword)) {
                substring_keyword_res.push_back(res);
        }
    } 

    vector<filesystem::path> keyword_files_sort;

    for(auto const& res: same_keyword_res) {
        keyword_files_sort.push_back(res);
    }

    for(auto const& res: prefix_keyword_res) {
        keyword_files_sort.push_back(res);
    }

    for(auto const& res: substring_keyword_res) {
        keyword_files_sort.push_back(res);
    }

    return keyword_files_sort;
}

// upper to lower letter
string upper_to_lower(string text) {
    
    for(int i = 0; i < text.length(); i++) {
        if(text[i] >= 65 && text[i] <= 90) {
            text[i] += 32;
        }
    }

    return text;
}
