#include <iostream>
#include <vector>
#include <QCoreApplication>

#include "rag.hpp"
#include "ollama.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    Document doc;

    doc.path = "test.txt";
    doc.text = "abcdefghij";

    vector<Document> documents = {doc};
    vector<Chunk> chunks = chunkDocuments(documents, 4, 2);

    cout << "chunk count: " << chunks.size() << endl;

    for(auto const& chunk : chunks) {
        cout << chunk.index << ": " << chunk.text << endl;
    }

    vector<float> a = getEmbedding("The transformer uses self-attention");
    cout << a.size() << endl;
    // vector<float> b = getEmbedding("Attention helps models understand relationships between tokens");

    // float score = cosineSimilarity(a, b);
    
    return 0;
}
