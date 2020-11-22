#include "Analyse.h"
#include "TableGen.h"
#include "FIRST.h"
#include "FOLLOW.h"
#include "WF.h"
#include "Main.h"

map<string, set<char> > FIRST;
map<string, set<char> > FOLLOW;
map<string, int> VN_dic;
vector<WF> VN_set;
bool used[MAX];
vector<map<char, string> > predict_table;

int main() {
    int n;
    char s[MAX];
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            int len = strlen(s), j;
            for (j = 0; j < len; j++)
                if (s[j] == '-') break;
            s[j] = 0;
            if (!VN_dic[s]) {
                VN_set.emplace_back(s);
                VN_dic[s] = VN_set.size();
            }
            int x = VN_dic[s] - 1;
            VN_set[x].insert(s + j + 2);
        }
        make_first();
        make_follow();
        make_table();
        string in;
        std::cin >> in;
        analyse(in);
    }
}