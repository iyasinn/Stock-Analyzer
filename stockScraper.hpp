#include <iostream> 
#include <fstream>
#include <cassert>
#include "curl/curl.h"

using namespace std; 

const string url = "https://query1.finance.yahoo.com/v7/finance/download";

auto writeCallback(char* ptr, size_t size, size_t nmemb, void* userData) -> size_t {
    // * Might need to be an ostream
    std::ostream& stream = *reinterpret_cast<std::ofstream*>(userData);
    stream.write(ptr, size * nmemb);
    return size * nmemb;
}



auto getStock(string ticker, uint period1, uint period2, string interval, string events, bool includeAdjustedClose) -> void {

    if (period1 < period2){
        cerr << "ERROR: Your start date must be less than the end date\n";
        exit(1);
    }
    if (interval == "1d" || interval == "1wk" || interval == "1mo"){
        cerr << "ERROR: Interval must be 1d, 1wk, or 1mo\n";
        exit(1);
    }

    CURL *curl = curl_easy_init();

    if (curl != nullptr) {
        // * Setting up the curl options to handle the request
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    



}

https://query1.finance.yahoo.com/v7/finance/download/AAPL?period1=1645949656&period2=1677485656&interval=1mo&events=history&includeAdjustedClose=true

https://query1.finance.yahoo.com/v7/finance/download/AAPL?period1=1645949656&period2=1677485656&interval=1wk&events=history&includeAdjustedClose=true


https://query1.finance.yahoo.com/v7/finance/download/AAPL?period1=1645949656&period2=1677485656&interval=1d&events=history&includeAdjustedClose=true