// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");

function lookupIdentifier(str) {
  switch (str) {
    case "else" :
        return /* ELSE */20;
    case "false" :
        return /* FALSE */18;
    case "fn" :
        return /* FUNCTION */22;
    case "if" :
        return /* IF */19;
    case "let" :
        return /* LET */23;
    case "return" :
        return /* RETURN */21;
    case "true" :
        return /* TRUE */17;
    default:
      return /* IDENT */Block.__(1, [str]);
  }
}

var Token = {
  lookupIdentifier: lookupIdentifier
};

function isLetter(ch) {
  if (ch >= "A" && ch <= "Z" || ch >= "a" && ch <= "z") {
    return true;
  } else {
    return ch === "_";
  }
}

function isDigit(ch) {
  if (ch >= "0") {
    return ch <= "9";
  } else {
    return false;
  }
}

function peekChar(l) {
  if (l.readPosition < l.input.length) {
    return l.input.charAt(l.readPosition);
  } else {
    return "";
  }
}

function readChar(l) {
  var ch = l.readPosition < l.input.length ? l.input.charAt(l.readPosition) : "";
  return {
          input: l.input,
          position: l.readPosition,
          readPosition: l.readPosition + 1 | 0,
          ch: ch
        };
}

function readIdentifier(originalLexer) {
  var startPosition = originalLexer.position;
  var l = originalLexer;
  while(isLetter(l.ch)) {
    l = readChar(l);
  };
  return /* tuple */[
          lookupIdentifier(l.input.substring(startPosition, l.position)),
          l
        ];
}

function readNumber(originalLexer) {
  var startPosition = originalLexer.position;
  var l = originalLexer;
  while(isDigit(l.ch)) {
    l = readChar(l);
  };
  return /* tuple */[
          /* INTEGER */Block.__(2, [Caml_format.caml_int_of_string(l.input.substring(startPosition, l.position))]),
          l
        ];
}

function readWhitespace(originalLexer) {
  var l = originalLexer;
  while(l.ch === " " || l.ch === "\t" || l.ch === "\n" || l.ch === "\r") {
    l = readChar(l);
  };
  return l;
}

function nextToken(l) {
  var l$1 = readWhitespace(l);
  var match = l$1.ch;
  var match$1;
  switch (match) {
    case "" :
        match$1 = /* tuple */[
          /* EOF */0,
          readChar(l$1)
        ];
        break;
    case "!" :
        match$1 = peekChar(l$1) === "=" ? /* tuple */[
            /* NOT_EQ */10,
            readChar(readChar(l$1))
          ] : /* tuple */[
            /* BANG */4,
            readChar(l$1)
          ];
        break;
    case "(" :
        match$1 = /* tuple */[
          /* LPAREN */13,
          readChar(l$1)
        ];
        break;
    case ")" :
        match$1 = /* tuple */[
          /* RPAREN */14,
          readChar(l$1)
        ];
        break;
    case "*" :
        match$1 = /* tuple */[
          /* ASTERISK */5,
          readChar(l$1)
        ];
        break;
    case "+" :
        match$1 = /* tuple */[
          /* PLUS */2,
          readChar(l$1)
        ];
        break;
    case "," :
        match$1 = /* tuple */[
          /* COMMA */11,
          readChar(l$1)
        ];
        break;
    case "-" :
        match$1 = /* tuple */[
          /* MINUS */3,
          readChar(l$1)
        ];
        break;
    case "/" :
        match$1 = /* tuple */[
          /* SLASH */6,
          readChar(l$1)
        ];
        break;
    case ";" :
        match$1 = /* tuple */[
          /* SEMICOLON */12,
          readChar(l$1)
        ];
        break;
    case "<" :
        match$1 = /* tuple */[
          /* LT */7,
          readChar(l$1)
        ];
        break;
    case "=" :
        match$1 = peekChar(l$1) === "=" ? /* tuple */[
            /* EQ */9,
            readChar(readChar(l$1))
          ] : /* tuple */[
            /* ASSIGN */1,
            readChar(l$1)
          ];
        break;
    case ">" :
        match$1 = /* tuple */[
          /* GT */8,
          readChar(l$1)
        ];
        break;
    case "{" :
        match$1 = /* tuple */[
          /* LBRACE */15,
          readChar(l$1)
        ];
        break;
    case "}" :
        match$1 = /* tuple */[
          /* RBRACE */16,
          readChar(l$1)
        ];
        break;
    default:
      match$1 = isLetter(l$1.ch) ? readIdentifier(l$1) : (
          isDigit(l$1.ch) ? readNumber(l$1) : /* tuple */[
              /* ILLEGAL */Block.__(0, [l$1.ch]),
              readChar(l$1)
            ]
        );
  }
  return /* tuple */[
          match$1[1],
          match$1[0]
        ];
}

function make(input) {
  return readChar({
              input: input[0],
              position: 0,
              readPosition: 0,
              ch: ""
            });
}

var Lexer = {
  isLetter: isLetter,
  isDigit: isDigit,
  peekChar: peekChar,
  readChar: readChar,
  readIdentifier: readIdentifier,
  readNumber: readNumber,
  readWhitespace: readWhitespace,
  nextToken: nextToken,
  make: make
};

exports.Token = Token;
exports.Lexer = Lexer;
/* No side effect */
