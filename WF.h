//
// Created by Ridd on 2020/11/22/022.
//

#ifndef LEX_WF_H
#define LEX_WF_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <set>

using namespace std;

//大写字母为非终止符(可以多一个'的标号做区分)，小写字母为终止符,用~代替epsilon
class WF {
public:
    string left;
    set<string> right;

    explicit WF(char s[]) {
        left = s;
    }

    void print() {
        printf("%s->", left.c_str());
        auto it = right.begin();
        if (right.begin() != right.end()) {
            printf("%s", it->c_str());
            it++;
        }
        for (; it != right.end(); it++)
            printf("|%s", it->c_str());
        puts("");
    }

    void insert(char s[]) {
        right.insert(s);
    }
};

#endif //LEX_WF_H
