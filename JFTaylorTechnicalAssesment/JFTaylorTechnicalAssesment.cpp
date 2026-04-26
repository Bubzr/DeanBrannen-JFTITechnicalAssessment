#include <iostream>
#include <vector>
#include <string>


//this region includes all of the classes used in this script
#pragma region Classes

//Class for all others to inherit from
class BaseClass {
public:
    //virtual functions for each class to check 'n' against their own rules and print their own responses from
    virtual bool shouldPrint(int n) = 0;
    virtual void print(int n) = 0;


    //checks each iterator from 1 to n against the inherited classes printing rules
    void printSolution(int n) {

       
       //here 'process' is a lamda function in case the number is less than 0.
       
        //lamda declaration
        auto process = [&](int i) {
            for (BaseClass* handler : handlers) {
                if (handler->shouldPrint(i)) {
                    handler->print(i);
                    break;
                }
            }
        };

        //runs appropriate for loop so that it starts at 1 or -1 
        if (n < 0)
            for (int i = -1; i >= n; i--) process(i);
        else
            for (int i = 1; i <= n; i++) process(i);
    }

    //adds classes to the BaseClass container
    void addHandler(BaseClass* handler) {
        handlers.push_back(handler);
    }


    //Cleanup for the BaseClass and Handlers, made with expansion in mind
    virtual ~BaseClass() {
        cleanHandler();
    }
    void cleanHandler() {
        for (BaseClass* handler : handlers) {
            delete handler;
        }
        handlers.clear();
    }
private:
    //private container for the different checks
    std::vector <BaseClass*> handlers;


};

//This region is for every class that inherits from the base class so they can make use of overriding virtual functions to suit their own needs
#pragma region Inherited classes

//multiple of 3 and 5 
class FizzBuzz : public BaseClass {
    bool shouldPrint(int n) override {
        return (n % 5 == 0 && n % 3 == 0);
    }

    void print(int n) override {
        std::cout << "FizzBuzz" << std::endl;
    }

};

//multiple of 3
class Fizz : public BaseClass {
    bool shouldPrint(int n) override {
        return (n % 3 == 0);
    }
    void print(int n) override {
        std::cout << "Fizz" << std::endl;
    }
};

//multiple of 5
class Buzz : public BaseClass {
    bool shouldPrint(int n) override {
        return (n % 5 == 0);
    }
    void print(int n) override {
        std::cout << "Buzz" << std::endl;
    }
};

//multiple of neither
class Number : public BaseClass {
    bool shouldPrint(int n) override {
        return (n % 5 != 0 && n % 3 != 0);
    }
    void print(int n) override {
        std::cout << std::to_string(n) << std::endl;
    }
};

#pragma endregion

#pragma endregion

int main()
{   
    
    //prompts user input
    int n;
    std::cout << "Please enter an integer: ";
    
    //Checks if the user input is a true integer and not a string, float or double
    while (!(std::cin >> n) || std::cin.peek() != '\n') {
        
        //if the response is not an integer the while loop will prompt the user again until it has found a viable entry
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please enter a whole number: ";
    }
    
    //Intializes handler vector and calls the print method in the base classes
    FizzBuzz* nHandler = new FizzBuzz();
    nHandler->addHandler(new FizzBuzz);
    nHandler->addHandler(new Fizz);
    nHandler->addHandler(new Buzz);
    nHandler->addHandler(new Number);

    nHandler->printSolution(n);

    //cleans pointers, vector cleanup in BaseClass destructor
    delete nHandler;
    return 0;
}

///QUESTION 3
/// <Application Summary>
/// This application takes a user supplied integer 'n' and iterates to n starting from 1 printing Fizz for multiples of 3, Buzz for multiples of 5, FizzBuzz for multiples of both, and the number itself for all other values.
/// The application has 3 main elements: the BaseClass which holds all functions and data structures, the inherited classes which override the virtual functions to implement their own rules, and the main function which drives the program.
/// These overrides are how we check the number against the rules mentioned earlier and print the desired outcome for each iterator from 1 to n.
/// In main we have a while loop that waits for user input so it can verify if we can use the input before running the rest of the script.
/// The Base Class has a vector for holding pointers to the inherited classes called 'handlers'. While we iterate from 1 to n
/// we also cycle through this vector to check the current iteration and display the proper response before ending the nested loop so we can move onto the next number.
/// The main function initializes the 'handlers' and places them in the vector in an order that ensures there is no other possible output that could have been skipped, meaning if it prints Buzz we can be confident that it was not meant to print Fizz or FizzBuzz.
/// The final step in the main function calls the destructor to the BaseClass which in turn cleans up the pointers in the vector and clears it so no memory leaks are present.
/// </Application Summary>
/// <returns></returns>

