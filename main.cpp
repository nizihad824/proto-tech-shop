  #include <iostream>
#include <iomanip>
using namespace std;

class Article
{
private:
    string model;
    double netprice;
    double taxRate;

public:
    Article(string _model, double _netprice, double _taxRate = 0.19)
    {
        model = _model;
        netprice = _netprice;
        taxRate = _taxRate;
    }

    virtual ~Article()
    {
        cout << "~Article() ";
        cout << model << endl;
    }

    void set_model(string m)
    {
        model = m;
    }

    void set_netPrice(double np)
    {
        netprice = np;
    }

    string get_model()
    {
        return model;
    }

    double get_netPrice()
    {
        return netprice;
    }

    double get_grossPrice()
    {
        return get_netPrice() + (get_netPrice() * taxRate);
    }

    virtual void print()
    {
    }
};

class Accessory : public Article
{
private:
    bool original;

public:
    Accessory(string model, double netprice, bool _original = true)
        : Article(model, netprice)
    {
        original = _original;
    }

    virtual ~Accessory()
    {
        cout << "~Accessory() ";
    }

    virtual void print()
    {
        cout << get_model();
        if(original)
        {
            cout << " (original accessory)";
        }
    }
};

enum OperatingSystem
{
    unknown, android, iOS, macOS, linux, proprietary, unix, windows
};

ostream& operator<<(ostream& out, const OperatingSystem& os)
{
    if(os == unknown)
    {
        out << "unknown OS";
    }
    else if(os == android)
    {
        out << "Android OS";
    }
    else if(os == iOS)
    {
        out << "iOS";
    }
    else if(os == macOS)
    {
        out << "MacOS";
    }
    else if(os == linux)
    {
        out << "Linux OS";
    }
    else if(os == proprietary)
    {
        out << "proprietary OS";
    }
    else if(os == unix)
    {
        out << "Unix OS";
    }
    else if(os == windows)
    {
        out << "MS Windows OS";
    }


    return out;
}

class Device : public Article
{
private:
    int main_memory;
    OperatingSystem os;

public:
    Device(string name, double netprice, int mainmemory, OperatingSystem _os = unknown)
            :Article(name, netprice)
    {
        main_memory = mainmemory;
        os = _os;
    }

    virtual ~Device()
    {
        cout << "~Device() ";
    }

    OperatingSystem get_os()
    {
        return os;
    }

    virtual void print()
    {
        cout << get_model() << ", RAM " << main_memory << " GB, " << os;
    }
};

class Notebook : public Device
{
private:
    string drive;
    bool convertible;

public:
    Notebook(string name, double netprice, int main_memory, string _drive,
             OperatingSystem _os = linux, bool _convertible = false)
             : Device(name, netprice, main_memory, _os)
    {
        drive = _drive;
        convertible = _convertible;
    }

    virtual ~Notebook()
    {
        cout << "~Notebook() ";
    }

    bool is_a_convertible()
    {
        return convertible;
    }

    virtual void print()
    {
        Device::print();
        if(is_a_convertible())
        {
            cout << "(convertible) ";
        }

        cout << drive;
    }
};

class Phone : public Device
{
public:
    Phone(string name, double netprice, int mainmemory = 4, OperatingSystem os = android) : Device(name, netprice, mainmemory, os)
    {
    }

    virtual ~Phone()
    {
        cout << "~Phone() ";
    }

    virtual void print()
    {
        Device::print();
        cout << " phone";
    }
};

class InCart
{
private:
    Article* article;
    int amount;
    InCart* next;

public:
    InCart(Article* artc, int _amount, InCart* _next)
    {
        article = artc;
        amount = _amount;
        next = _next;
    }

    virtual ~InCart()
    {
        cout << "~InCart() " << amount << " ";
        delete article;
    }

    Article* get_article()
    {
        return article;
    }

    int get_amount()
    {
        return amount;
    }

    void set_next(InCart* _next)
    {
        next = _next;
    }

    InCart* get_next()
    {
        return next;
    }

    virtual void print()
    {
        cout << amount << " ";
        article->print();
        cout << endl;
        cout << "\t\t\t\t\t";
        cout << fixed << setprecision(2);
        cout << article->get_grossPrice() << " EUR\t\t";
        cout << (article->get_grossPrice() * amount) << " EUR" << endl;
    }
};

class ShoppingCart
{
private:
    InCart* articles;
    double minFreeShipping;
    double sumNetPrice;
    double sumGrossPrice;

public:
    ShoppingCart()
    {
        articles = NULL;
        sumGrossPrice = 0.0;
        sumNetPrice = 0.0;
        minFreeShipping = 1000;
    }

    ~ShoppingCart()
    {
        cout << "~ShoppingCart()" << endl;

        InCart* temp = articles;
        InCart* next;
        while(temp)
        {
            next = temp->get_next();
            cout << "delete article: ";
            delete temp;
            temp = next;
        }
    }
//A public method with name article with an amount and pointer to an article as parameter ,
//adding a new object in cart on the heap to the shoppig cart and actuallising the two sum varible of the class properly
    void set_minFreeShipping(double fee)
    {
        minFreeShipping = fee;
    }

    void add_article(InCart* article)
    {
        if(articles == NULL)
        {
            article->set_next(articles);
            articles = article;
        }
        else
        {
            article->set_next(articles);
            articles = article;
        }

        sumGrossPrice += article->get_article()->get_grossPrice() * article->get_amount();
        sumNetPrice += article->get_article()->get_netPrice() * article->get_amount();
    }

    virtual void print()
    {
        InCart* temp = articles;
        while(temp)
        {
            temp->print();
            temp = temp->get_next();
        }

        double tax = sumGrossPrice - sumNetPrice;
        double shipping = 0;
        cout << "\t\t\t\t\t\t\t------------------"<<endl;
        cout << "\t\t\t\t\tsum net price:\t\t" << sumNetPrice << " EUR" << endl;
        cout << "\t\t\t\t\t\t  tax:\t\t" << tax << " EUR" << endl;
        cout << "\t\t\t\t      sum gross price:\t\t" << sumGrossPrice << " EUR" << endl;
        cout << "\t\t\t\t\t\t\t------------------"<<endl;
        if(sumGrossPrice < minFreeShipping)
        {
            shipping = 5.90;
        }
        cout << "\t\t\t\t\t     shipping:\t\t  " << shipping << " EUR" << endl;
        cout << "\t\t\t\t\t\t\t------------------"<<endl;
        cout << "\t\t\t\t\t\ttotal:\t\t" << sumGrossPrice+shipping << " EUR" << endl;
        cout << "\t\t\t\t\t\t\t=================="<<endl;
        cout << endl << endl;
     }
};

int main()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+                    P R O T O - T E C - S H O P                         +" << endl;
    cout << "+                 Y O U R  S H O P P I N H C A R T                       +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    ShoppingCart shoppingCart;
    shoppingCart.set_minFreeShipping(500);

    Article* powerbank = new Accessory("YOOLOX 10k Wireless Powerbank Qi", 31.08, false);
    InCart* cart1 = new InCart(powerbank, 3, NULL);
    shoppingCart.add_article(cart1);

    shoppingCart.print();

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+                    P R O T O - T E C - S H O P                         +" << endl;
    cout << "+                 Y O U R  S H O P P I N H C A R T                       +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    Article* phone = new Phone("Samsung Galaxy S10+ SM-G975F/DS Dual SIM", 661.67, 8);
    InCart* cart2 = new InCart(phone, 1, NULL);
    shoppingCart.add_article(cart2);

    Article* phone1 = new Phone("Apple iPhone 11 Pro 256GB", 1097.47, 4, iOS);
    InCart* cart3 = new InCart(phone1, 2, NULL);
    shoppingCart.add_article(cart3);

    Article* notebook = new Notebook("ASUS ROG Strix Scar III G731", 1586.55, 16, "512GB SSD + 1TB SSD", windows);
    InCart* cart4 = new InCart(notebook, 1, NULL);
    shoppingCart.add_article(cart4);

    shoppingCart.print();
    return 0;
}
