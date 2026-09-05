#include <vector> 
#include <filesystem>
#include <string>
#include <fstream>
#include <cmath>

#include "rag.hpp"

using namespace std;


vector<Document> loadDocuments(const string& dir_path) {
    vector<Document> document;
    
    for(auto const& dir_entry: filesystem::recursive_directory_iterator{dir_path}) {
        if(dir_entry.is_regular_file()) {
            if(dir_entry.path().extension() == ".txt" || dir_entry.path().extension() == ".md") {
                ifstream file(dir_entry.path().string());
                string content="", line;
                Document doc;

                while(getline(file, line)) {
                    content += line + "\n";
                }

                doc.path = dir_entry.path();
                doc.text = content;
                document.push_back(doc);
                
            }
        }
    }

    return document;
}

vector<Chunk> chunkDocuments(const vector<Document>& documents, size_t chunk_size, size_t overlap) {
    vector<Chunk> chunks;
    size_t stride;

    if(overlap >= chunk_size) {
        return chunks;
    }
    else {
        stride = chunk_size - overlap;
    }

    for(auto const& document : documents) {
        size_t start = 0, num_chunk = 0;
        while(start < document.text.length()){
            Chunk chunk;
            chunk.source = document.path;
            chunk.text =  document.text.substr(start, chunk_size);
            chunk.index = num_chunk;
            chunks.push_back(chunk);
            start += stride;
            num_chunk ++;
        }
    }

    return chunks;
}

float cosineSimilarity(const vector<float>& a, const vector<float>& b) {
    float numerator=0, denominator, powa=0, powb=0;

    for(int i = 0; i < a.size(); i++) {
        numerator += a[i] * b[i];
    }
    
    for(int i = 0; i < a.size(); i++) {
        powa += a[i] * a[i];
        powb += b[i] * b[i];
    }

    denominator = sqrt(powa) * sqrt(powb);

    return numerator/denominator;
}











