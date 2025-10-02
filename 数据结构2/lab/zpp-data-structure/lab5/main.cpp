#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int n;

bool z[510];


struct Magic {
    int heath;
    int delta;
    int index;
    bool triggered = false;
    vector<Magic> *m;
    queue<Magic *> *q;

    void decrease() {
        if (delta == 0 && !triggered) {
            triggered = true;
            for (int i = 0; i < n; ++i) {
                (*q).push(&(*m)[i]);
            }
        }
    }

    void print() {
        cout << index + 1 << " " << heath << " " << delta << " " << triggered << endl;
    }
};

vector<Magic> m;
queue<Magic *> q;


int main() {
    cin >> n;
    int cnt = 0;
    m = vector<Magic>(n);
    for (int i = 0; i < n; ++i) {
        m[i].m = &m;
        m[i].q = &q;
        m[i].index = i;
        cin >> m[i].heath;
        m[i].delta = m[i].heath / 2;
    }
    while (true) {
        if (all_of(z, z + n, [](bool a) {
            return a;
        })) {
            break;
        }
        sort(m.begin(), m.end(), [](Magic a, Magic b) {
            return a.delta < b.delta;
        });
        m[0].decrease();
        for (int i = 0; i < n; ++i) {
            m[i].print();
        }
        cout << "====" << endl;
        while (!q.empty()) {
            auto &h = q.front();
            q.pop();
            h->heath--;
            h->delta--;
            if (h->heath == 0) {
                z[h->index] = true;
            }
            if (h->delta == 0) {
                h->delta = INT_MAX;
            }
            h->decrease();
        }
        cnt++;
    }
    cout << cnt << endl;
}