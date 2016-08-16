#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
    type(type),
    position(position)
    {}
    
    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }
    
    char type;
    int position;
};

void exit(bool success, int position = 0)
{
    if (success)
    {
        std::cout << "Success" << std::endl;
    }
    else{
        std::cout << ++position << std::endl;
    }
    
    std::exit(0);
}

int main() {
    std::string text;
    getline(std::cin, text);
    
    std::stack <Bracket> opening_brackets_stack;
    for (int position { 0 }; position < text.length(); ++position) {
        char next = text[position];
        
        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));
        }
        
        if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.empty())
            {
                exit(false, position);
            }
            else if (!opening_brackets_stack.top().Matchc(next))
            {
                exit(false, position);
            }
            else
            {
                opening_brackets_stack.pop();
            }
        }
    }
    
    if (!opening_brackets_stack.empty())
    {
        for (size_t s { opening_brackets_stack.size() - 1 }; s > 0; --s)
        {
            opening_brackets_stack.pop();
        }
        exit(false, opening_brackets_stack.top().position);
    }
    
    exit(true);
}
