#include "trei.h"

Order* createorder()
{
    Order* order = new Order();

    // simple vanilla ice cream
    order->addIcecream(new SimpleIceCream("vanilla", 5.0));

    // pistachio ice cream with chocolate and caramel topping
    IceCream* pistachio = new SimpleIceCream("pistachio", 6.0);
    pistachio = new IcecreamWithChocolateTopping(pistachio);
    pistachio = new IcecreamWithCaramelTopping(pistachio);
    order->addIcecream(pistachio);

    // chocolate ice cream with caramel topping
    IceCream* chocolate = new SimpleIceCream("chocolate", 5.5);
    chocolate = new IcecreamWithCaramelTopping(chocolate);
    order->addIcecream(chocolate);

    // simple hazelnuts ice cream
    order->addIcecream(new SimpleIceCream("hazelnuts", 5.5));

    return order;
}
