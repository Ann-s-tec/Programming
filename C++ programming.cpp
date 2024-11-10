#include <iostream>
#include <string>
using namespace std;

class Electronics;
class Clothing;

class Product {
protected:
    string name;
    double price;

public:
    Product(const string& n = "", double p = 0.0) : name(n), price(p) {}

    virtual void setProductDetails() {
        cout << "\nEnter product name: ";
        cin >> name;
        cout << "Enter price: $";
        cin >> price;
    }

    virtual void displayProductDetails() const {
        cout << "Product Name: " << name << endl;
        cout << "Price: $" << price << endl;
    }

    virtual double getPrice() const {
        return price;
    }

    virtual ~Product() {
        cout << endl;
    }
};

class Electronics : public Product {
public:
    Electronics(const string& n, double p) : Product(n, p) {}

    void displayProductDetails() const override {
        cout << "\nElectronics: " << name << endl;
        cout << "Price: $" << price << endl;
    }
};

class Clothing : public Product {
public:
    Clothing(const string& n, double p) : Product(n, p) {}

    void displayProductDetails() const override {
        cout << "\nClothing: " << name << endl;
        cout << "Price: $" << price << endl;
    }
};

class ShoppingCart {
private:
    Product** products;
    int size;
    int capacity;
    double discountPercentage;

public:
    ShoppingCart(int initialCapacity = 2, double discount = 0.0) 
        : size(0), capacity(initialCapacity), discountPercentage(discount) {
        products = new Product*[capacity];
    }

    ~ShoppingCart() {
        for (int i = 0; i < size; ++i) {
            delete products[i];
        }
        delete[] products;
    }

    void addProduct(Product* product) {
        if (size == capacity) {
            capacity *= 2;
            Product** newProducts = new Product*[capacity];
            for (int i = 0; i < size; ++i) {
                newProducts[i] = products[i];
            }
            delete[] products;
            products = newProducts;
        }
        products[size++] = product;
    }

    void displayCart() const {
        for (int i = 0; i < size; ++i) {
            products[i]->displayProductDetails();
            cout << endl;
        }
    }

    double totalCost() const {
        double total = 0.0;
        for (int i = 0; i < size; ++i) {
            total += products[i]->getPrice();
        }
        return total;
    }

    double applyDiscount() const {
        double total = totalCost();
        return total * (1 - discountPercentage / 100); 
    }

    void setDiscount(double discount) {
        discountPercentage = discount;
    }

    double getDiscount() const {
        return discountPercentage;
    }
};

class Customer {
private:
    string custName;
    int age;
    string phoneNumber;
    Product** orderedProducts;
    int* quantities;
    int orderSize;

public:
    Customer() : orderedProducts(nullptr), quantities(nullptr), orderSize(0) {}

    ~Customer() {
        delete[] orderedProducts;
        delete[] quantities;
    }

    void setCustomerDetails(ShoppingCart& cart) {
        cout << "\nENTER CUSTOMER DETAILS" << endl;
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, custName);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter phone number: ";
        cin.ignore();
        getline(cin, phoneNumber);

        cout << "\nHow many products are in your order? ";
        cin >> orderSize;

        orderedProducts = new Product*[orderSize];
        quantities = new int[orderSize];

        for (int i = 0; i < orderSize; ++i) {
            int productType;
            cout << "\nSelect product type (1: Electronics, 2: Clothing): ";
            cin >> productType;

            string productName;
            double productPrice;

            if (productType == 1) {
                cout << "\nEnter the name of the electronic product: ";
                cin.ignore();  
                getline(cin, productName);  
                cout << "Enter the price of the electronic product: ";
                cin >> productPrice;  
                orderedProducts[i] = new Electronics(productName, productPrice);  
            } else if (productType == 2) {
                cout << "\nEnter the name of the clothing product: ";
                cin.ignore();  
                getline(cin, productName);  
                cout << "Enter the price of the clothing product: ";
                cin >> productPrice;  
                orderedProducts[i] = new Clothing(productName, productPrice);  
           } else {
                cout << "Invalid product type." << endl;
                --i;  
                continue;  
            }

            cout << "Enter the quantity: ";
            cin >> quantities[i];

            
            cart.addProduct(orderedProducts[i]);
        }
    }

    void displayCustomerDetails(const ShoppingCart& cart) const {
    cout << "\nCUSTOMER DETAILS" << endl;
    cout << "Customer Name: " << custName << endl;
    cout << "Age: " << age << endl;
    cout << "Phone Number: " << phoneNumber << endl;

    double totalOrderCost = 0.0;
    cout << "\nORDERED PRODUCT:" << endl;
    for (int i = 0; i < orderSize; ++i) {
        orderedProducts[i]->displayProductDetails();
        cout << "Quantity: " << quantities[i] << endl;
        double productTotalPrice = orderedProducts[i]->getPrice() * quantities[i];
        cout << "Total Price: $" << productTotalPrice << endl;
        totalOrderCost += productTotalPrice;
    }

    cout << "\nTotal Cost Before Discount: $" << totalOrderCost << endl;
    double totalAfterDiscount = totalOrderCost * (1 - cart.getDiscount() / 100);
    cout << "Total Cost After " << cart.getDiscount() << "% Discount: $" << totalAfterDiscount << endl;
}

};

class Feedback : public Customer {
private:
    int rating;
    string comments;

public:
    void setFeedbackDetails() {
        cout << "\n\tFEEDBACK" << endl;
        cout << "Enter rating (1-5): ";
        cin >> rating;
        cout << "Enter comments: ";
        cin.ignore();
        getline(cin, comments);
    }

    void displayFeedbackDetails() const {
        cout << "\n\tFEEDBACK" << endl;
        cout << "Rating: " << rating << endl;
        cout << "Comments: " << comments << endl;
    }
};

int main() {
    ShoppingCart cart;
    int numProducts;
    double discount;

    cout << "\t\t\tSHOPPY" << endl;
    cout << "\t\t*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "\n\nHow many products would you like to add to the cart? ";
    cin >> numProducts;

    cout << "\nEnter discount percentage (e.g., 10 for 10% off): ";
    cin >> discount;
    cart.setDiscount(discount); 

    for (int i = 0; i < numProducts; ++i) {
        int productType;
        cout << "\nSelect product type (1: Electronics, 2: Clothing): ";
        cin >> productType;

        string productName;
        double productPrice;

        if (productType == 1) {
            cout << "\nEnter the name of the electronic product: ";
            cin.ignore();
            getline(cin, productName);
            cout << "Enter the price of the electronic product: ";
            cin >> productPrice;
            cart.addProduct(new Electronics(productName, productPrice));
        } else if (productType == 2) {
            cout << "\nEnter the name of the clothing product: ";
            cin.ignore();
            getline(cin, productName);
            cout << "Enter the price of the clothing product: ";
            cin >> productPrice;
            cart.addProduct(new Clothing(productName, productPrice));
        } else {
            cout << "Invalid product type." << endl;
        }
    }

    cout << "\nProducts in the cart:" << endl;
    cart.displayCart();

    Customer customer;
    cout << "\n\n\t\t\tENTER CUSTOMER DETAILS" << endl;
    customer.setCustomerDetails(cart);
    cout << endl << "\n\t\t\tDISPLAYING ORDER DETAILS" << endl;
    customer.displayCustomerDetails(cart);

    Feedback feedback;
    cout << "\n\n\t\t\tENTER FEEDBACK" << endl;
    feedback.setFeedbackDetails();
    cout << endl << "\n\t\t\tDISPLAYING FEEDBACK " << endl;
    feedback.displayFeedbackDetails();

    
    return 0;
}
