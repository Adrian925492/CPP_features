#include "creation.hpp"

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>

//Creation 1: factory method


class Pixel {
public:
    static Pixel createFromRGB(int r, int g, int b) {
        std::cout << "Pixel created by RGB\n";
        return Pixel(r,g,b);
    }

    static Pixel createFromGRB(int g, int r, int b) {
        std::cout << "Pixel created by GRB\n";
        return Pixel(r,g,b);
    }
private:
    Pixel(int r, int g, int b) : _r(r), _g(g), _b(b) {}
    int _r, _g, _b;

    friend Pixel createPixel(int r, int g, int b);
};

//Creation 2: factory function
Pixel createPixel(int r, int g, int b) {
    std::cout << "Pixel created by function \n";
    return Pixel(r,g,b);
}

//Creation 3: by factory class
class ItemBase {
public:
    virtual void foo() = 0;
};

class Item1 : public ItemBase {
public:
    Item1() {
        std::cout << "Item1 created\n";
    }
    virtual void foo() override {
        std::cout << "Item1::foo()\n";
    }
};

class Item2 : public ItemBase {
public:
    Item2() {
        std::cout << "Item2 created\n";
    }
    virtual void foo() override {
        std::cout << "Item2::foo()\n";
    }
};

class ItemCreator {
public:
    using ItemType = std::unique_ptr<ItemBase>;
    using ConcreteCreator = ItemType(*)();  //Creator - call direct constructor with std::string_view as arg

    void registerItem(std::string_view name, ConcreteCreator creator) {
        creatorByExt.emplace(name, creator);    //Register creator and assigned (by name) item
    }

    ItemType create(std::string_view name) {
        if (name == "Item3")    //Example - special creation method for Item3
        {
            std::cout << "Item3 creation! \n";
            return {};
        } else {
            return creatorByExt.at(std::string(name))();
        }
    }
private:
    std::unordered_map<std::string, ConcreteCreator> creatorByExt;
};

//Builder example

struct A {
    std::string name;
    std::optional<std::string> param1;
    std::string description;
    std::string property;
    int x = 0;  // Initialize to avoid undefined behavior
};

//Base builder
template <typename ConcreteBuilder> class GenericABuilder {
public:
    explicit GenericABuilder(std::string name) : a_{.name = std::move(name)} {}

    A build() && {
        a_.description = "Build by builder!\n";     //Builder step
        return std::move(a_);  //return origin by r-value
    }

    ~GenericABuilder() {};

    ConcreteBuilder &&with_prop(std::string prop) {
        a_.property = std::move(prop);
        return static_cast<ConcreteBuilder &&> (*this);
    }

    ConcreteBuilder &&with_x(int x) {
        a_.x = std::move(x);
        return static_cast<ConcreteBuilder &&> (*this);
    }
private:
    A a_;
};

//Final builder type
class ABuilder final : public GenericABuilder<ABuilder> {
    using GenericABuilder<ABuilder>::GenericABuilder;
};

void creation_main() {
    std::cout << "Creation Mechanisms examples:\n";

    //Creation method usage example
    std::cout << "Create by method\n";
    auto pixel1 = Pixel::createFromRGB(1,2,3);
    auto pixel2 = Pixel::createFromGRB(20,10,30);
    
    //Creation function example
    std::cout << "Create by function\n";
    auto pixel3 = createPixel(11,12,13);

    //Creation by factory
    auto creator = ItemCreator{};

    creator.registerItem("Item1", []() -> ItemCreator::ItemType {
        return std::make_unique<Item1>();
    });

    creator.registerItem("Item2", []() -> ItemCreator::ItemType {
        return std::make_unique<Item2>();
    });

    std::cout << "Create by creation class\n";
    creator.create("Item1");
    creator.create("Item2");

    //Created by builder
    std::cout << "Create by builder example\n";
    //[ToCheck!]auto builder = ABuilder("A_item");
    //auto item = ABuilder{"A_Item"}.with_prop("some property").with_x(12).build();
    //std::cout << "Built item: " << item.name << ", property: " << item.property << ", x: " << item.x << "\n";
}
