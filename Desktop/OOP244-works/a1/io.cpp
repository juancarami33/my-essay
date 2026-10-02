#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring> 
#include "io.h"

using namespace std;

namespace seneca {

    void read(char* name) {
        cout << "Name\n> ";
        cin >> name;
    }

    void print(long long phone) {
        int area = phone / 10000000;
        int prefix = (phone % 10000000) / 10000;
        int line = phone % 10000;

        cout << "(" << setw(3) << setfill('0') << area << ") "
            << setw(3) << setfill('0') << prefix << "-"
            << setw(4) << setfill('0') << line << setfill(' '); 
    }

    void print(const PhoneRec& rec, size_t& row, const char* filter) {
        bool match = false;

        if (filter == nullptr) {
            match = true;
        }
        else if (strstr(rec.name, filter) != nullptr || strstr(rec.lastName, filter) != nullptr) {
            match = true;
        }

        if (match) {
            cout << row << ": " << rec.name << " " << rec.lastName << " ";
            print(rec.phone);
            cout << endl;
            row++;
        }
    }

    bool read(PhoneRec& rec, FILE* file) {
        if (file != nullptr) {
            int readCount = fscanf(file, "%s %s %lld", rec.name, rec.lastName, &rec.phone);
            return readCount == 3;
        }
        return false;
    }

    void print(PhoneRec* arr[], size_t size, const char* filter) {
        size_t row = 1;
        for (size_t i = 0; i < size; ++i) {
            print(*arr[i], row, filter);
        }
    }

    void setPointers(PhoneRec* ptrs[], PhoneRec recs[], size_t size) {
        for (size_t i = 0; i < size; ++i) {
            ptrs[i] = &recs[i];
        }
    }

    void sort(PhoneRec* ptrs[], size_t size, bool byLastName) {
        for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = i + 1; j < size; ++j) {
                if (byLastName) {
                    if (strcmp(ptrs[i]->lastName, ptrs[j]->lastName) > 0) {
                        PhoneRec* temp = ptrs[i];
                        ptrs[i] = ptrs[j];
                        ptrs[j] = temp;
                    }
                }
                else {
                    if (strcmp(ptrs[i]->name, ptrs[j]->name) > 0) {
                        PhoneRec* temp = ptrs[i];
                        ptrs[i] = ptrs[j];
                        ptrs[j] = temp;
                    }
                }
            }
        }
    }
}