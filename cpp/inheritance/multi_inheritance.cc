#include <iostream>

class BorrowableItem {
public:
    void checkOut() {
        std::cout << "BorrowableItem::checkOut()" << std::endl;
    }
};

class ElectronicGadget {
private:
    bool checkOut() const {
        std::cout << "ElectronicGadget::checkOut()" << std::endl;
        return true;
    }
};

class MP3Player : public BorrowableItem, public ElectronicGadget {

};

int main() {
    MP3Player mp3;
    mp3.BorrowableItem::checkOut(); // must specify base class name, otherwise it won't compile
    return 0;
}