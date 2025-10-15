#include "chai.hpp"

#include <chaiscript/chaiscript.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

// Example C++ function to expose to ChaiScript
int cpp_function(int x, int y) {
    return x + y;
}

// Example C++ class to expose to ChaiScript
class Calculator {
public:
    Calculator(int initial_value = 0) : value_(initial_value) {}
    
    int add(int n) { 
        value_ += n; 
        return value_; 
    }
    
    int multiply(int n) { 
        value_ *= n; 
        return value_; 
    }
    
    int get_value() const { return value_; }
    
private:
    int value_;
};

//Chaiscript - lightweight, build-in c++ header based scripting language. Allows to expose and use/run choosen c++ functions/classes etc. in text based script.

// Function to demonstrate loading and executing ChaiScript from external file
void execute_external_script_example(chaiscript::ChaiScript& chai, const std::string& script_path) {
    std::cout << "\n=== External Script File Example ===\n";
    
    try {
        // Check if file exists
        if (!std::filesystem::exists(script_path)) {
            std::cerr << "Script file not found: " << script_path << std::endl;
            return;
        }
        
        // Load the script file
        std::ifstream script_file(script_path);
        if (!script_file.is_open()) {
            std::cerr << "Failed to open script file: " << script_path << std::endl;
            return;
        }
        
        // Read the entire file content
        std::string script_content((std::istreambuf_iterator<char>(script_file)),
                                   std::istreambuf_iterator<char>());
        script_file.close();
        
        std::cout << "Loading script from: " << script_path << std::endl;
        std::cout << "Script size: " << script_content.size() << " characters\n\n";
        
        // Execute the script
        chai.eval(script_content);
        
        // Try to call a function defined in the external script
        std::cout << "\n=== Calling function from external script ===\n";
        try {
            auto greet_func = chai.eval<std::function<std::string(std::string)>>("greet_user");
            std::string greeting = greet_func("C++ Developer");
            std::cout << "Function result: " << greeting << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Note: Could not call greet_user function: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error executing external script: " << e.what() << std::endl;
    }
}

void chai_main()
{
    std::cout << "ChaiScript integration\n";
    
    try {
        // Create ChaiScript engine
        chaiscript::ChaiScript chai;
        
        // Bind C++ function to ChaiScript
        chai.add(chaiscript::fun(&cpp_function), "add_numbers");
        
        // Bind C++ class to ChaiScript
        chai.add(chaiscript::user_type<Calculator>(), "Calculator");
        chai.add(chaiscript::constructor<Calculator()>(), "Calculator");
        chai.add(chaiscript::constructor<Calculator(int)>(), "Calculator");
        chai.add(chaiscript::fun(&Calculator::add), "add");
        chai.add(chaiscript::fun(&Calculator::multiply), "multiply");
        chai.add(chaiscript::fun(&Calculator::get_value), "get_value");
        
        // ChaiScript already has function_exists built-in, so we don't need to add it
        
        // Execute ChaiScript code
        chai.eval("print(\"Hello from ChaiScript!\")");
        
        // Call C++ function
        chai.eval("var result = add_numbers(5, 3)");
        chai.eval("print(\"5 + 3 = \" + to_string(result))");
        
        // Use C++ class
        chai.eval("var calc = Calculator(10)");
        chai.eval("calc.add(5)");
        chai.eval("calc.multiply(2)");
        chai.eval("print(\"Calculator result: \" + to_string(calc.get_value()))");
        
        // Define ChaiScript function
        chai.eval(R"(
            def factorial(n) {
                if (n <= 1) {
                    return 1;
                } else {
                    return n * factorial(n - 1);
                }
            }
        )");
        
        chai.eval("print(\"Factorial of 5: \" + to_string(factorial(5)))");
        
        // Call ChaiScript function from C++
        auto chai_factorial = chai.eval<std::function<int(int)>>("factorial");
        int result = chai_factorial(6);
        std::cout << "Factorial of 6 (from C++): " << result << std::endl;
        
        // Demonstrate loading and executing script from external file
        std::string script_path = "source/chaiscript/example_script.chai";
        execute_external_script_example(chai, script_path);
        
    } catch (const std::exception& e) {
        std::cerr << "ChaiScript error: " << e.what() << std::endl;
    }
}