#include <string>
#include <filesystem>
#include <vector>

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

#include "search.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    QLineEdit *searchbar = new QLineEdit;
    QListWidget *result_list = new QListWidget;
    QPushButton *folder_button = new QPushButton("Select Folder");
    QLabel *folder_label = new QLabel("No folder selected");
    
    vector<filesystem::path> index;

    searchbar->setEnabled(false);
    
     // 選取指定資料夾
    QObject::connect(folder_button, &QPushButton::clicked, [&]() {
        QString selected_folder = QFileDialog::getExistingDirectory(&window, "Select Folder");

        if(!selected_folder.isEmpty()) {
            index = buildIndex(selected_folder.toStdString());
            searchbar->setEnabled(true);
           
            folder_label->setText(selected_folder);          
            result_list->clear();
        }
    });

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
    layout->addWidget(folder_button);
    layout->addWidget(folder_label);
    layout->addWidget(searchbar);
    layout->addWidget(result_list);

    window.setLayout(layout);

    window.setWindowTitle("Desktop Search");
    window.resize(600, 400);
    window.show();

    return app.exec();
}
