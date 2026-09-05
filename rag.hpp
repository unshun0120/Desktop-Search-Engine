#pragma once

#include <string>
#include <vector>
#include <filesystem>

// Struct
struct Document {
    std::filesystem::path path;
    std::string text;
};

struct Chunk {
    std::filesystem::path source;
    std::string text;
    size_t index; 
    std::vector<float> embedding;
};

struct RetrievalResult {
    size_t chunk_position;
    float score;
};


// Function Declaration
std::vector<Document> loadDocuments(const std::string& dir_path);

std::vector<Chunk> chunkDocuments(const std::vector<Document>& documents, size_t chunk_size, size_t overlap);

float cosineSimilarity(const std::vector<float>&a, const std::vector<float>& b);

void embedChunks(std::vector<Chunk>& chunks);

std::vector<RetrievalResult> retrieveTopK(const std::vector<Chunk>& chunks, const std::string& query, size_t k);


