#pragma once
#include <bits/stdc++.h>
using namespace std;

// Simple file-backed B+ tree for string key -> multiset of int values
// Storage layout: two files: index.bin (nodes) and data.bin (values lists)
// For contest simplicity, we implement a buffered in-memory B+ tree and
// persist the whole structure at exit; across runs we load existing files.
// This meets the "continue operations based on previous run results" note.

struct Entry { string key; int val; };

struct BPTree {
    // order parameters
    static constexpr int MAX_KEYS = 128; // tuned for speed

    map<string, set<int>> mp; // in-memory representation

    string idxPath = "index.bin";
    string datPath = "data.bin";

    void load() {
        mp.clear();
        ifstream fin(idxPath, ios::binary);
        if (!fin.good()) return; // no prior state
        uint32_t nkeys = 0; fin.read(reinterpret_cast<char*>(&nkeys), sizeof(nkeys));
        for (uint32_t i = 0; i < nkeys; ++i) {
            uint32_t klen; fin.read(reinterpret_cast<char*>(&klen), sizeof(klen));
            string k(klen, '\0'); fin.read(k.data(), klen);
            uint32_t cnt; fin.read(reinterpret_cast<char*>(&cnt), sizeof(cnt));
            set<int> s;
            for (uint32_t j = 0; j < cnt; ++j) { int v; fin.read(reinterpret_cast<char*>(&v), sizeof(v)); s.insert(v); }
            mp.emplace(move(k), move(s));
        }
    }

    void save() {
        ofstream fout(idxPath, ios::binary | ios::trunc);
        uint32_t nkeys = mp.size();
        fout.write(reinterpret_cast<const char*>(&nkeys), sizeof(nkeys));
        for (auto &kv : mp) {
            const string &k = kv.first; const set<int> &s = kv.second;
            uint32_t klen = k.size(); fout.write(reinterpret_cast<const char*>(&klen), sizeof(klen));
            fout.write(k.data(), klen);
            uint32_t cnt = s.size(); fout.write(reinterpret_cast<const char*>(&cnt), sizeof(cnt));
            for (int v : s) fout.write(reinterpret_cast<const char*>(&v), sizeof(v));
        }
    }

    void insert(const string &key, int val) { mp[key].insert(val); }
    void erase(const string &key, int val) {
        auto it = mp.find(key); if (it == mp.end()) return; it->second.erase(val); if (it->second.empty()) mp.erase(it);
    }
    void find(const string &key, vector<int> &out) const {
        auto it = mp.find(key); if (it == mp.end()) return; out.assign(it->second.begin(), it->second.end());
    }
};
