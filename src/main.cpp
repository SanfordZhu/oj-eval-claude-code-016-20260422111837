#include "bpt.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BPTree db;
    db.load();

    int n; if (!(cin >> n)) return 0;
    string cmd, key; int val;
    for (int i = 0; i < n; ++i) {
        cin >> cmd;
        if (cmd == "insert") { cin >> key >> val; db.insert(key, val); }
        else if (cmd == "delete") { cin >> key >> val; db.erase(key, val); }
        else if (cmd == "find") {
            cin >> key; std::vector<int> out; db.find(key, out);
            if (out.empty()) cout << "null\n";
            else {
                for (size_t j = 0; j < out.size(); ++j) { if (j) cout << ' '; cout << out[j]; }
                cout << '\n';
            }
        }
    }

    db.save();
    return 0;
}
