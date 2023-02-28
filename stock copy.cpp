#include <iostream>
#include <pugixml.hpp>
#include <fstream>
#include "curl/curl.h"

using namespace std; 

// tidy -config config.txt stockData.html >  output.html

auto writeCallback(char* ptr, size_t size, size_t nmemb, void* userData) -> size_t {
    std::ofstream& stream = *reinterpret_cast<std::ofstream*>(userData);
    // stream.write(ptr, size * nmemb);
    // return size * nmemb;

    for (int i = 0; i < size * nmemb; i++){
        stream << *ptr++;
    }

    return size * nmemb;
}

auto main() -> int{

    CURL *curl = curl_easy_init();
    string url = "https://finance.yahoo.com/quote/%5EIXIC/history?p=%5EIXIC";    
    string fileName = "stockDataa.html";
    ofstream file;
    file.open(fileName);

    // * CURL gets html 
    {
        if (curl != nullptr) {
            // * Setting up the curl options to handle the request
            // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
    }

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("output.html", pugi::parse_minimal);

    // Check if parsing was successful
    if (!result) {
        std::cerr << "Parsing error: " << result.description() << " " << result.offset << std::endl;
        return 1;
    }

    // Traverse the document tree and print the element names
    for (pugi::xml_node node = doc.first_child(); node; node = node.next_sibling()) {
        std::cout << "Element name: " << node.name() << std::endl;
    }

}

