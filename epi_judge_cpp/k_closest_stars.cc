#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_utils.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

struct Star {
    bool operator<(const Star& that) const {
        return Distance() < that.Distance();
    }

    double Distance() const { return sqrt(x * x + y * y + z * z); }

    double x, y, z;
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
                               const vector<Star>::const_iterator& stars_end,
                               int k) {
    priority_queue<Star> pq;

    double temp;
    for (; stars_begin != stars_end; stars_begin++) {
        temp = stars_begin->Distance();
        if (pq.size() < k) {
            pq.push(*stars_begin);
        } else if (temp < pq.top().Distance()) {
            pq.pop();
            pq.push(*stars_begin);
        }
    }

    vector<Star> result;
    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }
    // reverse(result.begin(), result.end());
    // return result;
    return {result.rbegin(), result.rend()};
}
template <>
struct SerializationTraits<Star> : UserSerTraits<Star, double, double, double> {
};

std::ostream& operator<<(std::ostream& out, const Star& s) {
    return out << s.Distance();
}

bool Comp(const vector<double>& expected, vector<Star> output) {
    if (output.size() != expected.size()) {
        return false;
    }

    std::sort(begin(output), end(output));

    for (int i = 0; i < output.size(); ++i) {
        if (!DefaultComparator()(output[i].Distance(), expected[i])) {
            return false;
        }
    }
    return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star>& stars, int k) {
    return FindClosestKStars(cbegin(stars), cend(stars), k);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"stars", "k"};
    return GenericTestMain(args, "k_closest_stars.cc", "k_closest_stars.tsv",
                           &FindClosestKStarsWrapper, &Comp, param_names);
}
