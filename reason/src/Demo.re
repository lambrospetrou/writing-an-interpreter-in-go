module Token {
  type t =
    | ILLEGAL(string)
    | EOF
    // Identifiers and literals
    | IDENT(string)
    | INTEGER(int)
    // Operators
    | ASSIGN
    | PLUS
    | MINUS
    | BANG
    | ASTERISK
    | SLASH
    | LT
    | GT
    | EQ
    | NOT_EQ
    // Delimeters
    | COMMA
    | SEMICOLON
    | LPAREN
    | RPAREN
    | LBRACE
    | RBRACE
    // Keywords
    | TRUE
    | FALSE
    | IF
    | ELSE
    | RETURN
    | FUNCTION
    | LET;

  let lookupIdentifier = (str: string): t => {
    switch(str) {
      | "fn" => FUNCTION
      | "let" => LET
      | "true" => TRUE
      | "false" => FALSE
      | "if" => IF
      | "else" => ELSE
      | "return" => RETURN
      | _ => IDENT(str)
    };
  }
}

module Lexer {
  type input = 
    | String(string)

  // TODO - Try with making the fields `mutable` as well?
  type lexer = {
    input: string,
    position: int,
    readPosition: int,
    ch: string
  }

  let isLetter = (ch) => (ch >= "A" && ch <= "Z") || (ch >= "a" && ch <= "z") || ch == "_";
  let isDigit =  (ch) => (ch >= "0" && ch <= "9");

  let peekChar = (l: lexer): string => {
    l.readPosition < Js.String.length(l.input) 
      ? Js.String.charAt(l.readPosition, l.input)
      : "";
  }

  let readChar = (l: lexer): lexer => {
    let ch = l.readPosition < Js.String.length(l.input) 
      ? Js.String.charAt(l.readPosition, l.input)
      : "";

    {
      ...l,
      ch,
      position: l.readPosition,
      readPosition: l.readPosition + 1
    }
  }

  let readIdentifier = (originalLexer: lexer): (Token.t, lexer) => {
    let startPosition = originalLexer.position;
    let l = ref(originalLexer);
    while (isLetter(l^.ch)) {
      l := readChar(l^);
    };

    (Token.lookupIdentifier(Js.String.substring(~from=startPosition, ~to_=l^.position, l^.input)), l^);
  }

  let readNumber = (originalLexer: lexer): (Token.t, lexer) => {
    let startPosition = originalLexer.position;
    let l = ref(originalLexer);
    while (isDigit(l^.ch)) {
      l := readChar(l^);
    };

    (
      Token.INTEGER(
        int_of_string(Js.String.substring(~from=startPosition, ~to_=l^.position, l^.input))
      ), 
      l^
    );
  }

  let readWhitespace = (originalLexer: lexer): lexer => {
    let l = ref(originalLexer);
    while (l^.ch == " " || l^.ch == "\t" || l^.ch == "\n" || l^.ch == "\r") {
        l := readChar(l^);
    }
    l^
  }

  let nextToken = (l: lexer): (lexer, Token.t) => {
    let l = readWhitespace(l);

    // TODO Do better than this duplication :(
    let (token, newLexer) = switch (l.ch) {
      | "=" => {
        if (peekChar(l) == "=") {
          (Token.EQ, readChar(readChar(l)))
        } else {
          (Token.ASSIGN, readChar(l))
        }
      }
      | "+" => (Token.PLUS, readChar(l))
      | "-" => (Token.MINUS, readChar(l))
      | "!" => {
        if (peekChar(l) == "=") {
          (Token.NOT_EQ, readChar(readChar(l)))
        } else {
          (Token.BANG, readChar(l))
        }
      }
      | "*" => (Token.ASTERISK, readChar(l))
      | "/" => (Token.SLASH, readChar(l))
      | "<" => (Token.LT, readChar(l))
      | ">" => (Token.GT, readChar(l))
      | ";" => (Token.SEMICOLON, readChar(l))
      | "," => (Token.COMMA, readChar(l))
      | "(" => (Token.LPAREN, readChar(l))
      | ")" => (Token.RPAREN, readChar(l))
      | "{" => (Token.LBRACE, readChar(l))
      | "}" => (Token.RBRACE, readChar(l))
      | "" => (Token.EOF, readChar(l))
      | _ => {
        if (isLetter(l.ch)) {
          readIdentifier(l);
        } else if (isDigit(l.ch)) {
          readNumber(l);
        } else {
          (Token.ILLEGAL(l.ch), readChar(l));
        }
      }
    };

    (newLexer, token);
  }

  let make = (input: input): lexer => {
    switch (input) {
      | String(inputString) => readChar({
        input: inputString,
        position: 0,
        readPosition: 0,
        ch: ""
      })
    }
  }
}
