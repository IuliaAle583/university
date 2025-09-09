#include "altsub3.h"

int runStair()
{
    Stair* s1 = new WoodStair(20);
    cout << s1->getDescription() << " - " << s1->getPrice() << endl;

    Stair* s2 = new StairWithHandrail(
        new MetalStair(10),
        new MetalHandrail(),
        5.0
    );
    cout << s2->getDescription() << " - " << s2->getPrice() << endl;

    Stair* s3 = new StairWithHandrail(
        new WoodStair(10),
        new HandrailWithVerticalElements(new WoodHandrail(), 10),
        5.0
    );
    cout << s3->getDescription() << " - " << s3->getPrice() << endl;

    delete s1;
    delete s2;
    delete s3;

    return 0;
}

