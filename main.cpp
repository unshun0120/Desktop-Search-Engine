#include<iostream>
#include<filesystem>

using namespace std;

int main() {
	string dir_path = R"(D:\github\desktop-search-engine\test_data)";
	string path="", keyword;
    
    cout << "search> ";
    cin >> keyword;
        
	for(auto const& dir_entry: filesystem::recursive_directory_iterator{dir_path}) {
        if(dir_entry.is_regular_file()) {
            path = dir_entry.path().filename().string();
            if(path.find(keyword) != string::npos)
                cout << dir_entry.path() << endl;
        }
    }

   
    return 0;
}
