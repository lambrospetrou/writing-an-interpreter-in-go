open Jest;

describe("Token", () => {
  open Expect;
  open Demo;

  test("lookupIdentifier", () => {
    expect((
      Token.lookupIdentifier("fn"),
      Token.lookupIdentifier("let"),
      Token.lookupIdentifier("random_identifier")
    )) |> toEqual((
      Token.FUNCTION,
      Token.LET,
      Token.IDENT("random_identifier")
    ));
  });
});

describe("Lexer", () => {
  open Expect;
  open Demo;

  describe("nextToken", () => {
    let gatherTokens = (input) => {
      let lexer = Lexer.make(String(input));
      let chars = Js.String.split("", input);

      let (_lexer, tokens) = Js.Array.reduce(((lexer, tokens), _) => {
        let (l, token) = Lexer.nextToken(lexer);
        token == Token.EOF ? (l, tokens) : (l, Array.concat([tokens, [|token|]]))
      }, (lexer, [||]), chars);

      tokens
    };

    test("simple", () => {
      let input = "=+(){},;|";
      expect(gatherTokens(input))
      |> toEqual([|
        Token.ASSIGN,
        Token.PLUS,
        Token.LPAREN,
        Token.RPAREN,
        Token.LBRACE,
        Token.RBRACE,
        Token.COMMA,
        Token.SEMICOLON,
        Token.ILLEGAL("|")
      |])
    });

    test("multi-line", () => {
      let input = "
        let five = 5;
        let ten = 10;

        let add = fn   (x, y) {
          x + y;
        };

        let result = add(five, ten);";

      expect(gatherTokens(input))
      |> toEqual([|
        Token.LET,
        Token.IDENT("five"),
        Token.ASSIGN,
        Token.INTEGER(5),
        Token.SEMICOLON,
        Token.LET,
        Token.IDENT("ten"),
        Token.ASSIGN,
        Token.INTEGER(10),
        Token.SEMICOLON,
        Token.LET,
        Token.IDENT("add"),
        Token.ASSIGN,
        Token.FUNCTION,
        Token.LPAREN,
        Token.IDENT("x"),
        Token.COMMA,
        Token.IDENT("y"),
        Token.RPAREN,
        Token.LBRACE,
        Token.IDENT("x"),
        Token.PLUS,
        Token.IDENT("y"),
        Token.SEMICOLON,
        Token.RBRACE,
        Token.SEMICOLON,
        Token.LET,
        Token.IDENT("result"),
        Token.ASSIGN,
        Token.IDENT("add"),
        Token.LPAREN,
        Token.IDENT("five"),
        Token.COMMA,
        Token.IDENT("ten"),
        Token.RPAREN,
        Token.SEMICOLON,
      |])
    });

  });
});
