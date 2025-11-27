#include <bits/stdc++.h>

using namespace std;

class ConsistentHashRing {
private:
    map<int, string> ring;
    set<int> sorted_keys;
    int replicas;

    int get_hash(const string& value) {
        hash<string> hash_function;
        return hash_function(value);
    }

public:
    ConsistentHashRing(int replicas = 3) : replicas(replicas) {}

      // Function to add Node in the ring
    void add_node(const string& node) {
        for (int i = 0; i < replicas; ++i) {
            int replica_key = get_hash(node + "_" + to_string(i));
            ring[replica_key] = node;
            sorted_keys.insert(replica_key);
        }
    }

      // Function to remove Node from the ring
    void remove_node(const string& node) {
        for (int i = 0; i < replicas; ++i) {
            int replica_key = get_hash(node + "_" + to_string(i));
            ring.erase(replica_key);
            sorted_keys.erase(replica_key);
        }
    }

    string get_node(const string& key) {
        if (ring.empty()) {
            return "";
        }

        int hash_value = get_hash(key);
        auto it = sorted_keys.lower_bound(hash_value);

        if (it == sorted_keys.end()) {
            // Wrap around to the beginning of the ring
            it = sorted_keys.begin();
        }

        return ring[*it];
    }
};

int main() {
    ConsistentHashRing hash_ring;

    // Add nodes to the ring
    hash_ring.add_node("Node_A");
    hash_ring.add_node("Node_B");
    hash_ring.add_node("Node_C");

    // Get the node for a key
    string key = "first_key";
    string node = hash_ring.get_node(key);

    cout << "The key '" << key << "' is mapped to node: " << node << endl;

    return 0;
}
