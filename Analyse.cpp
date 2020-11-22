#include "Analyse.h"
#include "TableGen.h"
#include "FIRST.h"
#include "FOLLOW.h"
#include "WF.h"

extern map<string, set<char> > FIRST;
extern map<string, set<char> > FOLLOW;
extern map<string, int> VN_dic;
extern vector<WF> VN_set;
extern bool used[MAX];
extern vector<map<char, string> > predict_table;

void print(int steps, stack<string> stk, string src, const string &wf, int x) {
    printf("%-10d", steps);
    string out;
    while (!stk.empty()) {
        out = stk.top() + out;
        stk.pop();
    }
    printf("#%-9s", out.c_str());
    out = "";
    for (int i = x; i < src.length(); i++)
        out += src[i];
    printf("%-10s", (out + "#").c_str());
    printf("%-10s\n", wf.c_str());
}

void analyse(const string &src) {
    stack<string> stk;
    stk.push("E");
    int steps = 0;
    int idx = 0;
    printf("%-14s%-14s%-14s%-14s\n", "步骤", "符号栈", "输入串", "所用产生式");
    while (!stk.empty()) {
        string u = stk.top();
        string tmp;
        stk.pop();
        if (!isupper(u[0])) {
            if (idx == src.length() && u[0] == '~');
            else if (src[idx] == u[0])
                idx++;
        } else {
            int x = VN_dic[u] - 1;
            tmp = predict_table[x][src[idx]];
            for (int i = tmp.length() - 1; i >= 0; i--) {
                if (tmp[i] == '\'') {
                    string v = tmp.substr(i - 1, 2);
                    stk.push(v);
                    i--;
                } else {
                    string v = tmp.substr(i, 1);
                    stk.push(v);
                }
            }
            tmp = u + "->" + tmp;
        }
        print(steps++, stk, src, tmp, idx);
    }
}
