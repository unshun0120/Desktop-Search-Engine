#pragma once
#include<filesystem>
#include<string>
#include<vector>

std::vector<std::filesystem::path> buildIndex(std::string);
std::vector<std::filesystem::path> searchFiles(const std::vector<std::filesystem::path>&, std::string);



