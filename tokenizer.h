#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

namespace calc {
    class Tokenizer {
      private:
        std::vector<Token> tokens;

      public:
        Tokenizer(std::string const inputString);

        enum class TokenType {

        };

        struct Token {
            TokenType type;
            std::string value;
        };
    };
} // namespace calc

#endif // TOKENIZER_H
