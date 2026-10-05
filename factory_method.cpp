#include <iostream>
#include <memory>
#include <string>

// ==========================================
// 1. PRODUCT INTERFACE & CONCRETE PRODUCTS
// ==========================================

// The abstract Base Product
class Product { // Vehicle
public:
    virtual ~Product() = default; // Virtual destructor is crucial for correct cleanup
    virtual std::string Operation() const = 0;
};

// Concrete Product A
class ConcreteProductA : public Product { // Truck
public:
    std::string Operation() const override {
        return "{Result of ConcreteProductA}";
    }
};

// Concrete Product B
class ConcreteProductB : public Product { // Aeroplane
public:
    std::string Operation() const override {
        return "{Result of ConcreteProductB}";
    }
};

// ==========================================
// 2. CREATOR INTERFACE & CONCRETE CREATORS
// ==========================================

// The Base Creator declares the factory method
class Creator {
public:
    virtual ~Creator() = default;

    // The core Factory Method
    virtual std::unique_ptr<Product> FactoryMethod() const = 0;

    // The Creator's primary responsibility is NOT creating products. 
    // It usually contains core business logic that relies on the Product object.
    std::string SomeOperation() const {
        // Call the factory method to create a Product object.
        std::unique_ptr<Product> product = this->FactoryMethod(); // Truck or Aeroplane 
        // Use the product.
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        return result;
    }
};

// Concrete Creator A overrides the factory method to produce Product A
class ConcreteCreatorA : public Creator { // Factory that builds Trucks
public:
    std::unique_ptr<Product> FactoryMethod() const override {
        return std::make_unique<ConcreteProductA>();
    }
};

// Concrete Creator B overrides the factory method to produce Product B
class ConcreteCreatorB : public Creator { // Factory that builds Aeroplane
public:
    std::unique_ptr<Product> FactoryMethod() const override {
        return std::make_unique<ConcreteProductB>();
    }
};

class ConcreteCreatorC : public Creator {
    
};

// =================================
// 3. CLIENT CODE
// ==========================================

// The client works with an instance of a concrete creator through its base interface
void ClientCode(const Creator& creator) {
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n" << creator.SomeOperation() << std::endl;
}

int main() {
    std::cout << "App: Launched with ConcreteCreatorA.\n";
    std::unique_ptr<Creator> creatorA = std::make_unique<ConcreteCreatorA>();
    ClientCode(*creatorA);
    
    std::cout << "\nApp: Launched with ConcreteCreatorB.\n";
    std::unique_ptr<Creator> creatorB = std::make_unique<ConcreteCreatorB>();
    ClientCode(*creatorB);

    return 0;
}