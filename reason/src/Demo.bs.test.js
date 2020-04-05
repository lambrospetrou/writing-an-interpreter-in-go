// FIXME - Rewrite this in Reason https://github.com/glennsl/bs-jest
const {Lexer, Token} = require("./Demo.bs");

describe.skip("Lexer", () => {
  it("should parse simple tokens", () => {
    const input = "=+(){},;£";
    let l = Lexer.make([input]), token = undefined;
    input.split("").forEach(_ => {
      [l, token] = Lexer.nextToken(l);
      console.log(l, token);
    });
  });

  it("should parse vars and functions", () => {
    const input = `
    let five = 5;
    let ten = 10;

    let add = fn(x, y) {
      x + y;
    };

    let result = add(five, ten);
    `
    let l = Lexer.make([input]), token = undefined;
    input.split("").forEach(_ => {
      [l, token] = Lexer.nextToken(l);
      console.log(l, token);
    });
  });
});
