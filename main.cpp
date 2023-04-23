#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

pair<string, string> StringSplitter(string &someString){
    size_t where = someString.find(':');
    string name = someString.substr(0, where);
    string age = someString.substr(where+1, someString.size());
    pair<string, string> nameandage;
    nameandage.first = name;
    nameandage.second = age;
    return nameandage;
}

struct Human{
    string name;
    string age;
};

void printToJson(std::vector<Human>& people) {
    std::ofstream file("sorted.json");
    file << "{\n";
    file << "\t\"sorted_by_name_gt\" : [";
    bool first = true;
    sort(people.begin(), people.end(), [](Human a, Human b){ // лямбда функция омагад
        return a.name < b.name;
    });
    for (const auto& person : people) {
        if (!first) file << ", ";
        file << "{\"name\": \"" << person.name << "\", \"age\": " << person.age << "}";
        first = false;
    }
    file << "],\n";
    file << "\t\"sorted_by_age_less\" : [";
    first = true;
    sort(people.begin(), people.end(), [](Human a, Human b){ // лямбда функция омагад
        return a.age > b.age;
    });
    for (const auto& person : people) {
        if (!first) file << ", ";
        file << "{\"name\": \"" << person.name << "\", \"age\": " << person.age << "}";
        first = false;
    }
    file << "]\n";
    file << "}";
    file.close();
}


int main(int argc, char *argv[]) {
    vector<Human> unsortedVector;
    for (int i=1; i<argc; i++) {
        string s(argv[i]);
        unsortedVector.push_back({StringSplitter(s).first, StringSplitter(s).second});
    }
    printToJson(unsortedVector);

}
