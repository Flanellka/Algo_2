#include "../ht.cpp"

void TestInsertAndGet() {
    HashTable ht(10);
    ht.Insert("AAA", 100);
    ht.Insert("BIG", 200);

    int value;
    assert(ht.Get("AAA", value) && value == 100);
    assert(ht.Get("BIG", value) && value == 200);
    std::cout << "TestInsertAndGet passed" << std::endl;
}

void TestUpdateValue() {
    HashTable ht(10);
    ht.Insert("AAA", 100);
    ht.Insert("AAA", 150);
    int value;
    assert(ht.Get("AAA", value) && value == 150);
    std::cout << "TestUpdateValue passed" << std::endl;
}

void TestRemove() {
    HashTable ht(10);
    ht.Insert("AAA", 100);
    bool removed = ht.Remove("AAA");
    int value;
    assert(removed);
    assert(!ht.Get("AAA", value));
    std::cout << "TestRemove passed" << std::endl;
}

int main() {
    TestInsertAndGet();
    TestUpdateValue();
    TestRemove();
    return 0;
}
