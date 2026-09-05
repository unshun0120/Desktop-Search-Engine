#pragma once

#include <string>
#include <vector>
#include <filesystem>

struct Document {
    std::filesystem::path path;
    std::string text;
};

struct Chunk {
    std::filesystem::path source;
    std::string text;
    size_t index; 
};

std::vector<Document> loadDocuments(const std::string& dir_path);

std::vector<Chunk> chunkDocuments(const std::vector<Document>& documents, size_t chunk_size, size_t overlap);

float cosineSimilarity(const std::vector<float>&a, const std::vector<float>& b);


