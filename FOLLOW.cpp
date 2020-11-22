#include "FOLLOW.h"
#include "WF.h"

extern map<string, set<char> > FIRST;
extern map<string, set<char> > FOLLOW;
extern map<string, int> VN_dic;
extern vector<WF> VN_set;
extern bool used[MAX];
extern vector<map<char, string> > predict_table;

void append(const string &str1, const string &str2) {
    set<char> &from = FOLLOW[str1];
    set<char> &to = FOLLOW[str2];
    auto it = from.begin();
    for (; it != from.end(); it++)
        to.insert(*it);
}

void make_follow() {
    while (true) {
        bool goon = false;
        for (int i = 0; i < VN_set.size(); i++) {
            string &left = VN_set[i].left;
            set<string> &right = VN_set[i].right;
            auto it = right.begin();
            for (; it != right.end(); it++) {
                bool flag = true;
                const string &str = *it;
                for (int j = it->length() - 1; j >= 0; j--) {
                    if (str[j] == '\'') {
                        int x = VN_dic[it->substr(j - 1, 2)] - 1;
                        if (flag) {
                            int tt = FOLLOW[it->substr(j - 1, 2)].size();
                            append(left, it->substr(j - 1, 2));
                            int tt1 = FOLLOW[it->substr(j - 1, 2)].size();
                            if (tt1 > tt) goon = true;
                            if (!VN_set[x].right.count("~"))
                                flag = false;
                        }
                        for (int k = j + 1; k < it->length(); k++) {
                            if (isupper(str[k])) {
                                string id;
                                if (k != it->length() - 1 && str[k + 1] == '\'')
                                    id = it->substr(k, 2);
                                else id = it->substr(k, 1);
                                set<char> &from = FIRST[id];
                                set<char> &to = FOLLOW[it->substr(j - 1, 2)];
                                int tt = to.size();
                                auto it1 = from.begin();
                                for (; it1 != from.end(); it1++)
                                    if (*it1 != '~')
                                        to.insert(*it1);
                                int tt1 = FOLLOW[it->substr(j - 1, 2)].size();
                                if (tt1 > tt) goon = true;
                                if (!VN_set[VN_dic[id] - 1].right.count("~"))
                                    break;
                            } else if (str[k] != '\'') {
                                int tt = FOLLOW[it->substr(j - 1, 2)].size();
                                FOLLOW[it->substr(j - 1, 2)].insert(str[k]);
                                int tt1 = FOLLOW[it->substr(j - 1, 2)].size();
                                if (tt1 > tt)
                                    goon = true;
                                break;
                            } else continue;
                        }
                        j--;
                    } else if (isupper(str[j])) {
                        int x = VN_dic[it->substr(j, 1)] - 1;
                        if (flag) {
                            int tt = FOLLOW[it->substr(j, 1)].size();
                            append(left, it->substr(j, 1));
                            if (!VN_set[x].right.count("~"))
                                flag = false;
                            int tt1 = FOLLOW[it->substr(j, 1)].size();
                            if (tt1 > tt) goon = true;
                        }
                        for (int k = j + 1; k < it->length(); k++) {
                            if (isupper(str[k])) {
                                string id;
                                if (k != it->length() - 1 && str[k + 1] == '\'')
                                    id = it->substr(k, 2);
                                else id = it->substr(k, 1);
                                set<char> &from = FIRST[id];
                                set<char> &to = FOLLOW[it->substr(j, 1)];
                                auto it1 = from.begin();
                                int tt = FOLLOW[it->substr(j, 1)].size();
                                for (; it1 != from.end(); it1++)
                                    if (*it1 != '~')
                                        to.insert(*it1);
                                int tt1 = FOLLOW[it->substr(j, 1)].size();
                                if (tt1 > tt) goon = true;
                                if (!VN_set[VN_dic[id] - 1].right.count("~"))
                                    break;
                            } else if (str[k] != '\'') {
                                int tt = FOLLOW[it->substr(j, 1)].size();
                                FOLLOW[it->substr(j, 1)].insert(str[k]);
                                int tt1 = FOLLOW[it->substr(j, 1)].size();
                                if (tt1 > tt) goon = true;
                                break;
                            } else continue;
                        }
                    } else flag = false;
                }
            }
        }
        if (!goon) break;
    }
#define DEBUG
#ifdef DEBUG
    puts("****************FOLLOW**********************");
    auto it = FOLLOW.begin();
    for (; it != FOLLOW.end(); it++) {
        printf("$FOLLOW(%s)=\\{", it->first.c_str());
        set<char> &temp = it->second;
        temp.insert('#');
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