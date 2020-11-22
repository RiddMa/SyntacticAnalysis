#include "FIRST.h"
#include "WF.h"

extern map<string, set<char> > FIRST;
extern map<string, set<char> > FOLLOW;
extern map<string, int> VN_dic;
extern vector<WF> VN_set;
extern bool used[MAX];
extern vector<map<char, string> > predict_table;

void dfs(int x) {
    if (used[x]) return;
    used[x] = true;
    string &left = VN_set[x].left;
    set<string> &right = VN_set[x].right;
    auto it = right.begin();
    for (; it != right.end(); it++)
        for (int i = 0; i < it->length(); i++) {
            if (!isupper(it->at(i)) && it->at(i) != '\'') {
                FIRST[left].insert(it->at(i));
                break;
            }
            if (isupper(it->at(i))) {
                int y;
                if (i != it->length() - 1 && it->at(i + 1) == '\'')
                    y = VN_dic[it->substr(i, 2)] - 1;
                else y = VN_dic[it->substr(i, 1)] - 1;
                string &tleft = VN_set[y].left;
                dfs(y);
                set<char> &temp = FIRST[tleft];
                auto it1 = temp.begin();
                bool flag = true;
                for (; it1 != temp.end(); it1++) {
                    if (*it1 == '~') flag = false;
                    FIRST[left].insert(*it1);
                }
                if (flag) break;
            } else continue;
        }
}

void make_first() {
    memset(used, 0, sizeof(used));
    for (int i = 0; i < VN_set.size(); i++)
        dfs(i);
#define DEBUG
#ifdef DEBUG
    puts("****************FIRST**********************");
    auto it = FIRST.begin();
    for (; it != FIRST.end(); it++) {
        printf("$FIRST(%s)=\\{", it->first.c_str());
        set<char> &temp = it->second;
        auto it1 = temp.begin();
        bool flag = false;
        for (; it1 != temp.end(); it1++) {
            if (flag) printf(",");
            printf("%c", *it1);
            flag = true;
        }
        puts("\\}$");
    }
#endif
}