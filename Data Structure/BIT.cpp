struct BIT {
    vector<int> bi;

    BIT(int sz) : bi(sz + 1, 0) {}

    void update(int idx, int val) {
        for (++idx; idx < bi.size() ; idx = idx + (idx & -idx)) {
            bi[idx] += val;
        }
    }

    int find(int idx) {
        if (idx < 0) return 0;
        int ret = 0;
        for (++idx; idx; idx = idx - (idx & -idx)) {
            ret+= bi[idx];
        }
        return ret;
    }

    int get(int r1, int r2) {
        return find(r2) - find(r1 - 1);
    }
}