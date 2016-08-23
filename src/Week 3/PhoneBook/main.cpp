#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using std::string;
using std::unordered_map;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}

vector<string> process_queries2(const vector<Query>& queries)
{
    vector<string> results;
    
    unordered_map<int, string> phone_book;
    
    for (size_t i = 0; i < queries.size(); ++i)
    {
        if (queries[i].type == "add")
        {
            phone_book[queries[i].number] = queries[i].name;
        }
        else if (queries[i].type == "del")
        {
            phone_book.erase(queries[i].number);
        }
        else
        {
            auto iter_result = phone_book.find(queries[i].number);
            if (iter_result != phone_book.end())
            {
                results.emplace_back(iter_result->second);
            }
            else
            {
                results.emplace_back("not found");
            }
        }
    }
    
    return results;
}

int main() {
    //write_responses(process_queries(read_queries()));
    write_responses(process_queries2(read_queries()));
    return 0;
}
