#include "train.cpp"

int main() {
    // sitting wagon with no upper seats
    Sitting sc(10, 0, 5, 0, false);
    // has all the types of seats
    Platzkart pc(6, 6, 3, 3, false);
    // no side seats
    Coupe cc(6, 6, 0, 0, true);
    // no side seats and upper seats
    SV svc(6, 0, 0, 0, true);

    PassengerTrain train;
    train.add(&sc);
    train.add(&pc);
    train.add(&cc);
    train.add(&svc);

    double profit = train.getTotalProfit();
    std::cout << "Money from sitting wagon: " << sc.getProfit() << std::endl;
    std::cout << "Money from platczkart wagon: " << pc.getProfit() << std::endl;
    std::cout << "Money from coupe wagon: " << cc.getProfit() << std::endl;
    std::cout << "Money from SV: " << svc.getProfit() << std::endl;
    std::cout << "All profit: " << profit << std::endl;
    return 0;
}
