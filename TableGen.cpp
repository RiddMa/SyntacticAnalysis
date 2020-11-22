#include "TableGen.h"
#include "WF.h"

extern map<string, set<char> > FIRST;
extern map<string, set<char> > FOLLOW;
extern map<string, int> VN_dic;
extern vector<WF> VN_set;
extern bool used[MAX];
extern vector<map<char, string> > predict_table;

//检查一个字符是否属于一个字符串的FIRST集合
bool check_first(const string &text, char ch) {
    for (int i = 0; i < text.length(); i++) {
        bool hasEmpty = false;
        if (!isupper(text[i]) && text[i] != '\'') {
            if (text[i] != ch) return false;
            else return true;
        } else if (isupper(text[i])) {
            string temp;
            if (i != text.length() - 1 && text[i + 1] == '\'')
                temp = text.substr(i, 2);
            else
                temp = text.substr(i, 1);
            set<char> &dic = FIRST[temp];
            auto it = dic.begin();
            for (; it != dic.end(); it++) {
                if (*it == '~') hasEmpty = true;
                if (*it == ch) return true;
            }
            if (!hasEmpty) break;
        } else continue;
    }
    return false;
}

//检查一个字符是否属于一个字符串的FOLLOW集合
bool check_follow(const string &text, char ch) {
    set<char> &dic = FOLLOW[text];
    auto it = dic.begin();
    for (; it != dic.end(); it++)
        if (*it == ch) return true;
    return false;
}

void make_table() {
    map<char, string> temp;
    vector<char> letter;
    bool vis[500];
    memset(vis, 0, sizeof(vis));
    for (auto &i : VN_set) {
        set<string> &right = i.right;
        auto it = right.begin();
        for (; it != right.end(); it++)
            for (char j : *it)
                if (!isupper(j) && j != '\'') {
                    if (vis[j]) continue;
                    vis[j] = true;
                    letter.push_back(j);
                }
    }
    for (auto &i : VN_set) {
        temp.clear();
        string &left = i.left;
        set<string> &right = i.right;
        auto it = right.begin();
        for (; it != right.end(); it++)
            for (char &j : letter) {
                //cout << *it << " " <<  letter[j] << endl;
                if (check_first(*it, j)) {
                    //cout << "YES" << endl;
                    temp[j] = *it;
                }
                if (it->at(0) == '~' && check_follow(left, j))
                    temp[j] = *it;
            }
        predict_table.push_back(temp);
    }
#define DEBUG
#ifdef DEBUG
    for (int i = 0; i <= (letter.size() + 1) * 10; i++)
        printf("-");
    puts("");
    printf("|%9s", "|");
    for (char i : letter)
        printf("%5c%5s", i, "|");
    puts("");
    for (int i = 0; i <= (letter.size() + 1) * 10; i++)
        printf("-");
    puts("");
    for (int i = 0; i < VN_set.size(); i++) {
        printf("|%5s%4s", VN_set[i].left.c_str(), "|");
        for (char &j : letter)
            if (predict_table[i].count(j))
                printf("%7s%3s", predict_table[i][j].c_str(), "|");
            else printf("%10s", "|");
        puts("");
        for (int j = 0; j <= (letter.size() + 1) * 10; j++)
            printf("-");
        puts("");
    }
#endif
}