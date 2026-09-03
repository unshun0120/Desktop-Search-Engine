#include <string>
#include <filesystem>
#include <vector>

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>

#include "search.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QLineEdit *searchbar = new QLineEdit;
    QListWidget *result_list = new QListWidget;
    
    string dir_path = R"(D:\github\desktop-search-engine\test_data)";
    vector<filesystem::path> index;
    index = buildIndex(dir_path);

    // 搜尋欄
    searchbar->setPlaceholderText("Search files...");

    QObject::connect(searchbar, &QLineEdit::returnPressed, [&]() {
        string keyword = searchbar->text().toStdString();
        result_list->clear();    
        
        vector<filesystem::path> keyword_results = searchFiles(index, keyword);

        if(keyword_results.empty()){
            result_list->addItem("No file found.");
        }
        else{
            for(auto const& file: keyword_results){
                result_list->addItem(QString::fromStdString(file.string()));
            }
        }

    });
    
    // 排版
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(searchbar);
    layout->addWidget(result_list);

    window.setLayout(layout);

    window.setWindowTitle("Desktop Search");
    window.resize(600, 400);
    window.show();

    return app.exec();
}
