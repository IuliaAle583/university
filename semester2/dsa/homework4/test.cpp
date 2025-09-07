#include "MultiMap.h"
#include <cassert>
#include <iostream>

void testMostFrequent() {
    MultiMap mm;
    assert(mm.mostFrequent() == NULL_TVALUE);
    mm.add(1, 100);
    assert(mm.mostFrequent() == 100);
    mm.add(2, 200);
    mm.add(3, 300);
    TValue mf = mm.mostFrequent();
    assert(mf == 100 || mf == 200 || mf == 300);
    mm.add(4, 100);
    mm.add(5, 100);
    mm.add(6, 200);
    assert(mm.mostFrequent() == 100);
    MultiMap mm2;
    mm2.add(1, 10);
    mm2.add(2, 20);
    mm2.add(3, 10);
    mm2.add(4, 20);
    TValue mf2 = mm2.mostFrequent();
    assert(mf2 == 10 || mf2 == 20);

    cout << "All tests passed for frequency.\n";
}
