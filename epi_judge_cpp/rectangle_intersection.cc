#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include <tuple>
struct Rect {
    int x, y, width, height;
};

Rect IntersectRectangle(const Rect& R1, const Rect& R2) {
    Rect s, b;
    Rect inter;
    if (R1.x < R2.x) {
        s = R1;
        b = R2;
    } else {
        s = R2;
        b = R1;
    }
    bool xIntersect = false;
    if (s.x + s.width >= b.x) {
        xIntersect = true;
    }

    if (xIntersect) {
        inter.x = b.x;
        inter.width = std::min(s.x + s.width, b.x + b.width) - inter.x;
    }

    if (R1.y < R2.y) {
        s = R1;
        b = R2;
    } else {
        s = R2;
        b = R1;
    }
    bool yIntersect = false;
    if (s.y + s.height >= b.y) {
        yIntersect = true;
    }

    if (yIntersect) {
        inter.y = b.y;
        inter.height = std::min(s.y + s.height, b.y + b.height) - inter.y;
    }

    if (xIntersect && yIntersect) {
        return inter;
    } else {
        return {0, 0, -1, -1};
    }
}

bool operator==(const Rect& r1, const Rect& r2) {
    return std::tie(r1.x, r1.y, r1.width, r1.height) ==
           std::tie(r2.x, r2.y, r2.width, r2.height);
}

template <>
struct SerializationTraits<Rect> : UserSerTraits<Rect, int, int, int, int> {
    static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
        return {FmtStr("area({})", arg_name), FmtStr("perimeter({})", arg_name),
                FmtStr("max(w, h)({})", arg_name)};
    }

    static std::vector<int> GetMetrics(const Rect& x) {
        return {x.height * x.width, 2 * (x.height + x.width),
                std::max(x.height, x.width)};
    }
};

std::ostream& operator<<(std::ostream& out, const Rect& r) {
    return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"R1", "R2"};
    return GenericTestMain(args, "rectangle_intersection.cc",
                           "rectangle_intersection.tsv", &IntersectRectangle,
                           DefaultComparator{}, param_names);
}
