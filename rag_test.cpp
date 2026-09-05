#include <iostream>
#include <vector>
#include <QCoreApplication>

#include "rag.hpp"
#include "ollama.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    Document doc;

    /*doc.path = "test.txt";
    doc.text = "abcdefghij";

    vector<Document> documents = {doc};
    vector<Chunk> chunks = chunkDocuments(documents, 4, 2);

    cout << "chunk count: " << chunks.size() << endl;

    for(auto const& chunk : chunks) {
        cout << chunk.index << ": " << chunk.text << endl;
    } */


    Chunk a;
    a.text = "Transformer uses self-attention.";

    Chunk b;
    b.text = "Attention helps models understand relationships between tokens.";

    Chunk c;
    c.text = "I like eating pizza for dinner.";

    vector<Chunk> chunks = {a, b, c};
    
    embedChunks(chunks);

    string query = "How does attention work?";
    

    vector<RetrievalResult> result_chunks = retrieveTopK(chunks, query, 2);
    for(auto const& res : result_chunks) {
        cout << res.score << endl;
        cout << chunks[res.chunk_position].text << endl;
    }


    return 0;
}
