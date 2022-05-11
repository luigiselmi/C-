#include "gui/std_lib_facilities.h"

class Token {
  public:
    char kind;
    double value;

    Token(char k) : kind{k}, value{0} { }
    Token(char k, double v) : kind{k}, value{v} { }
};

class Token_stream {
  public:
    Token get();                // get a Token
    void putback(Token t);      // put a token back
    void ignore(char c);
  private:
    bool full { false };        // is there a Token in the buffer?
    Token buffer {'0'};         // here is where putback() stores a Token
};

const char quit = 'q';
const char print = ';';
const char number = '8'; // let '8' represent a number

void Token_stream::putback(Token t) {
    if (full) error("putback() into a full buffer");
    buffer = t;                 // copy t to buffer
    full = true;                // buffer is now full
}

Token Token_stream::get() {
  if (full) {             // do we already have a Token?
    full = false;       // remove Token from buffer
    return buffer;
  }

  char ch;
  cin >> ch;              // note that >> skips whitespace

  switch (ch) {
    case print:
    case quit:
    case '(': case ')': case '{': case '}': case '!':
    case '+': case '-': case '*': case '/':
      return Token { ch };
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': {
      cin.putback(ch);    // put digit back into input stream
      double val;
      cin >> val;
      return Token { number, val };
    }
    default:
      error("Bad token");
  }
}

void Token_stream::ignore(char c) {  // c represents the kind of Token
  // first look in buffer:
  if (full && c==buffer.kind) {
    full = false;
    return;
  }
  full = false;
  // now search input:
  char ch = 0;
  while (cin>>ch)
    if (ch==c) return;
}

Token_stream ts;            // provides get() and putback()
double expression();        // forward declaration for primary to call

double primary() {           // deal with numbers and parenthesis
  Token t = ts.get();
  switch (t.kind) {
    case '(': {                   // handle '(' expression ')'
      double d = expression();
      t = ts.get();
      if (t.kind != ')') error("')' expected");
        return d;
    }
    case '{': {
      double d = expression();
      t = ts.get();
      if (t.kind != '}') error("'}' expected");
        return d;
    }
    case number:                   // we use '8' to represent a number
      return t.value;         // return the number's value
    case '-':
      return -primary();
    case '+':
      return primary();

    default:
      error("primary expected");
  }
}

double secondary() {        // ex 3 - Add a factorial operator '!'
  double left = primary();
  Token t = ts.get();

  while (true) {
    if (t.kind == '!') {
      if (left == 0)
        return 1;

      for (int i = left - 1; i > 0; --i)
        left *= i;

      t = ts.get();
    }
    else {
      ts.putback(t);
      return left;
    }
  }
}

double term() {              // deal with * and /
  double left = secondary();
  Token t = ts.get();             // get next token from Token_stream

  while (true) {
    switch (t.kind) {
      case '*':
        left *= secondary();
        t = ts.get();
        break;
      case '/': {
        double d = secondary();
        if (d == 0) error("divide by zero");
        left /= d;
        t = ts.get();
        break;
      }
      default:
        ts.putback(t);      // put t back into the Token_stream
        return left;
    }
  }
}

double expression() {         // deal with + and -

  double left = term();           // read and evaluate a term
  Token t = ts.get();             // get next token from Token_stream

  while (true) {
    switch (t.kind) {
      case '+':
        left += term();     // evaluate term and add
        t = ts.get();
        break;
      case '-':
        left -= term();     // evaluate term and subtract
        t = ts.get();
        break;
      default:
        ts.putback(t);      // put t back into the token stream
        return left;
    }
  }
}

void clean_up_mess() {
  ts.ignore(print);
}

const char prompt = '>';

void calculate() {
  double val = 0;
  while (cin)
    try {
    cout << prompt;
    Token t = ts.get();
    while (t.kind == print) t = ts.get();
    if (t.kind == quit) return;
    ts.putback(t);
    cout << "=" << expression() << "\n";
    }
    catch (exception& e) {
      cerr << e.what() << "\n";
      clean_up_mess();
    }
}

int main() {
  try {
    calculate();
    keep_window_open();
    return 0;
  }
  catch(exception& e) {
    cerr << "Exception: " << e.what() << '\n';
    keep_window_open("~~");
  }
  catch(...) {
    cerr << "Unknown exception\n";
    keep_window_open("~~");
    return 2;
  }
}
