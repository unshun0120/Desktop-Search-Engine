#include<iostream>
#include<filesystem>
#include<vector>

using namespace std;

vector<filesystem::path> searchFiles(string, string);

int main() {
	string dir_path = R"(D:\github\desktop-search-engine\test_data)";
	string path="", keyword;
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



