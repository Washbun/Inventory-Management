#include<iostream>
#include<conio.h>
#include<string>
#include<vector>
#include<limits>
#include<fstream>
#include<sstream>
using namespace std;
class Inventory
{
public:
    virtual void displayInventory() const = 0;
    virtual bool findProduct(int id, int& quantity, double& price) const = 0;
    virtual bool updateStock(int id, int quantityChange) = 0;
    virtual void addProduct() = 0;
    virtual void saveInventoryToFile(const string &filename) const = 0;
    virtual void loadInventoryFromFile(const string &filename) = 0;
};
class NonPerishable:public Inventory
{
private:
    struct Product
    {
        string name;
        int id, quantity;
        double price;
    };
    vector<Product> inventory;
public:
    NonPerishable()
    {
        loadInventoryFromFile("nonperishable_inventory.txt");
    }
    void addProduct() override
    {
        Product newProduct;
        cout << "Enter Product ID:";
        cin >> newProduct.id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Product Name:";
        getline(cin, newProduct.name);
        while (true)
        {
            try
            {
                cout << "Enter Product Quantity:";
                cin >> newProduct.quantity;
                if (cin.fail())
                {
                    throw invalid_argument("Invalid input for quantity. Please enter an integer value");
                }
                if (newProduct.quantity < 0)
                {
                    throw invalid_argument("Quantity cannot be negative. Please enter a positive integer");
                }
                break;
            }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        while (true)
        {
            try
            {
                cout << "Enter Product Price:";
                cin >> newProduct.price;
                if (cin.fail())
                {
                    throw invalid_argument("Invalid input for price. Please enter a decimal value");
                }
                if (newProduct.price < 0)
                {
                    throw invalid_argument("Price cannot be negative. Please enter a positive value");
                }
                break;
            }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        inventory.push_back(newProduct);
        cout << "Product added successfully to Non Perishable Inventory" << endl;
        saveInventoryToFile("nonperishable_inventory.txt");
    }
    void displayInventory() const override
    {
        if (inventory.empty())
        {
            cout << "Non Perishable Inventory is empty" << endl;
            return;
        }
        cout << "\nNon Perishable Inventory List:\n";
        for (const auto& product : inventory)
        {
            cout << "ID: " << product.id << " | Name: " << product.name << " | Quantity: " << product.quantity << " | Price: Rs" << product.price << endl;
        }
    }
    bool findProduct(int id, int& quantity, double& price) const override
    {
        for (const auto& product : inventory)
        {
            if (product.id == id && product.quantity > 0)
            {
                quantity = product.quantity;
                price = product.price;
                return true;
            }
        }
        return false;
    }
    bool updateStock(int id, int quantityChange) override
    {
        for (auto &product:inventory)
        {
            if (product.id == id)
            {
                if (product.quantity + quantityChange < 0)
                {
                    cout << "Not enough stock available" << endl;
                    return false;
                }
                product.quantity += quantityChange;
                saveInventoryToFile("nonperishable_inventory.txt");
                return true;
            }
        }
        cout << "Product not found in Non Perishable Inventory" << endl;
        return false;
    }
    void saveInventoryToFile(const string &filename) const override
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto& product : inventory)
            {
                file << product.id << '|' << product.name << '|' << product.quantity << '|' << product.price << '\n';
            }
            file.close();
        }
        else
        {
            cerr << "Failed to open" << filename << "for writing!" << endl;
        }
    }
    void loadInventoryFromFile(const string& filename) override
    {
        ifstream file(filename);
        if (file.is_open())
        {
            inventory.clear();
            Product product;
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                ss >> product.id;
                ss.ignore();
                getline(ss, product.name, '|');
                ss >> product.quantity;
                ss.ignore();
                ss >> product.price;
                inventory.push_back(product);
            }
            file.close();
        }
        else
        {
            cout << "No existing nonperishable inventory file found.Starting fresh." << endl;
        }
    }
};
class Perishable :public Inventory
{
private:
    struct Product
    {
        string name;
        int id, quantity;
        double price;
    };
    vector<Product> inventory;
public:
    Perishable()
    {
        loadInventoryFromFile("perishable_inventory.txt");
    }
    void addProduct() override
    {
        Product newProduct;
        cout << "Enter Product ID:";
        cin >> newProduct.id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Product Name:";
        getline(cin, newProduct.name);
        while (true)
        {
            try
            {
                cout << "Enter Product Quantity:";
                cin >> newProduct.quantity;
                if (cin.fail())
                {
                    throw invalid_argument("Invalid input for quantity. Please enter an integer value");
                }
                if (newProduct.quantity < 0)
                {
                    throw invalid_argument("Quantity cannot be negative. Please enter a positive integer");
                }
                break;
            }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        while (true)
        {
            try
            {
                cout << "Enter Product Price:";
                cin >> newProduct.price;
                if (cin.fail())
                {
                    throw invalid_argument("Invalid input for price. Please enter a decimal value");
                }
                if (newProduct.price < 0)
                {
                    throw invalid_argument("Price cannot be negative. Please enter a positive value");
                }
                break;
            }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        inventory.push_back(newProduct);
        cout << "Product added successfully to Perishable Inventory" << endl;
        saveInventoryToFile("perishable_inventory.txt");
    }
    void displayInventory() const override
    {
        if (inventory.empty())
        {
            cout << "Perishable Inventory is empty" << endl;
            return;
        }
        cout << "\nPerishable Inventory List:\n";
        for (const auto& product : inventory)
        {
            cout << "ID: " << product.id << " | Name: " << product.name << " | Quantity: " << product.quantity << " | Price: Rs" << product.price << endl;
        }
    }
    bool findProduct(int id, int& quantity, double& price) const override
    {
        for (const auto& product : inventory)
        {
            if (product.id == id && product.quantity > 0)
            {
                quantity = product.quantity;
                price = product.price;
                return true;
            }
        }
        return false;
    }
    bool updateStock(int id, int quantityChange) override
    {
        for (auto& product : inventory)
        {
            if (product.id == id)
            {
                if (product.quantity + quantityChange < 0)
                {
                    cout << "Not enough stock available" << endl;
                    return false;
                }
                product.quantity += quantityChange;
                saveInventoryToFile("perishable_inventory.txt");
                return true;
            }
        }
        cout << "Product not found in Non Perishable Inventory" << endl;
        return false;
    }
    void saveInventoryToFile(const string& filename) const override
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto& product : inventory)
            {
                file << product.id << '|' << product.name << '|' << product.quantity << '|' << product.price << '\n';
            }
            file.close();
        }
        else
        {
            cerr << "Failed to open" << filename << "for writing!" << endl;
        }
    }
    void loadInventoryFromFile(const string& filename) override
    {
        ifstream file(filename);
        if (file.is_open())
        {
            inventory.clear();
            Product product;
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                ss >> product.id;
                ss.ignore();
                getline(ss, product.name, '|');
                ss >> product.quantity;
                ss.ignore();
                ss >> product.price;
                inventory.push_back(product);
            }
            file.close();
        }
        else
        {
            cout << "No existing perishable inventory file found.Starting fresh." << endl;
        }
    }
};
class Customer
{
private:
    string name,contactNumber,address;
public:
    void inputDetails()
    {
        cout << "Enter Customer Name:";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter Customer Contact Number:";
        getline(cin, contactNumber);
        cout << "Enter Customer Address:";
        getline(cin, address);
    }
    string getName() const
    {
        return name;
    }
    string getContactNumber() const
    {
        return contactNumber;
    }
    string getAddress() const
    {
        return address;
    }
};
class Discount
{
private:
    double discountThreshold,discountPercentage;
public:
    Discount(double threshold, double percentage) :discountThreshold(threshold), discountPercentage(percentage)
    {}
    double applyDiscount(double totalAmount) const
    {
        if (totalAmount > discountThreshold)
        {
            double discountAmount = (discountPercentage / 100.0) * totalAmount;
            return totalAmount - discountAmount;
        }
        return totalAmount;
    }
    void displayDiscountInfo() const
    {
        cout << "Discount applies when total amount exceeds Rs " << discountThreshold << " with a " << discountPercentage << "% discount" << endl;
    }
};
class Order
{
private:
    struct OrderItem
    {
        int productId;
        double price;
        int quantity;
        string inventoryType;
    };
    vector<OrderItem>orderedItems;
    double totalCost;
    Customer customer;
    bool customerDetailsSet;
    Discount discount;
public:
    Order(double discountThreshold,double discountPercentage):totalCost(0.0),customerDetailsSet(false),discount(discountThreshold,discountPercentage)
    {}
    void setCustomerDetails()
    {
        if(!customerDetailsSet)
        customer.inputDetails();
        customerDetailsSet = true;
    }
    void placeOrder(Inventory *inventory)
    {
        int productId,quantity;
        double price;
        inventory->displayInventory();
        cout << "Enter the Product ID to order: ";
        cin >> productId;
        if (inventory->findProduct(productId, quantity, price))
        {
            while (true)
            {
                try
                {
                    cout << "Enter quantity to order: ";
                    cin >> quantity;
                    if (cin.fail())
                    {
                        throw invalid_argument("Invalid input for quantity. Please enter an integer value");
                    }
                    if (quantity < 0)
                    {
                        throw invalid_argument("Quantity cannot be negative. Please enter a positive integer");
                    }
                    break;
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (inventory->updateStock(productId, -quantity))
            {
                orderedItems.push_back({ productId,price,quantity,typeid(*inventory).name() });
                totalCost += quantity * price;
                cout << "Order placed for Product ID: " << productId << " Quantity: " << quantity << endl;
            }
        }
        else
        {
            cout << "Product is out of Stock" << endl;
        }
    }
    void displayOrderSummary() const
    {
        double finalAmount = discount.applyDiscount(totalCost);
        cout << "\nOrder Summary for Customer: " << customer.getName() << endl;
        cout << "Contact Number: " << customer.getContactNumber() << endl;
        cout << "Address: " << customer.getAddress() << endl;
        cout << "Original Total Cost: Rs" << totalCost << endl;
        cout << "Total Cost after Discount: Rs" <<finalAmount<< endl;
        discount.displayDiscountInfo();
        cout << "Ordered Products:\n";
        for (const auto& item : orderedItems)
        {
            cout << "ID: " << item.productId << " | Quantity: " << item.quantity << " | Price: Rs" << item.price << " | From Inventory: " << item.inventoryType << endl;
        }
    }
};
int main()
{
    NonPerishable nonperishable;
    Perishable perishable;
    double discountThreshold = 100.0;
    double discountPercentage = 10.0;
    int choice;
    Order order(discountThreshold, discountPercentage);
    do
    {
        cout << "\n===============Menu===============\n" << endl;
        cout << "1.Order from Non Perishable Inventory" << endl;
        cout << "2.Order from Perisable Inventory" << endl;
        cout << "3.Add a Product to Non Perishable Inventory" << endl;
        cout << "4.Add a Product to Perishable Inventory" << endl;
        cout << "5 View the Non Perishable Inventory" << endl;
        cout << "6.View the Perishable Inventory" << endl;
        cout << "7.Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            order.setCustomerDetails();
            order.placeOrder(&nonperishable);
            order.displayOrderSummary();
            break;
        } 
        case 2:
        {
            order.setCustomerDetails();
            order.placeOrder(&perishable);
            order.displayOrderSummary();
            break;
        }
        case 3:nonperishable.addProduct();
            break;
        case 4:perishable.addProduct();
            break;
        case 5:nonperishable.displayInventory();
            break;
        case 6:perishable.displayInventory();
            break;
        case 7:exit(0);
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }while (choice != 7);
    _getch();
    return 0;
}
